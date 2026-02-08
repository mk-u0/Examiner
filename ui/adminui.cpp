#include "adminui.h"
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(AdminFrame, wxFrame)
    EVT_MENU(wxID_EXIT, AdminFrame::OnExit)
        wxEND_EVENT_TABLE()

            AdminFrame::AdminFrame(const wxString &username)
    : wxFrame(nullptr, wxID_ANY, "Exam Dashboard - " + username,
              wxDefaultPosition, wxSize(900, 600)),
      m_username(username),
      m_questionsPanel(nullptr),
      m_questionsTableSizer(nullptr),
      m_pageLabel(nullptr),
      m_currentPage(1)
{
    LoadQuestionsFromDatabase();

    wxPanel *mainPanel = new wxPanel(this);
    mainPanel->SetBackgroundColour(wxColour(70, 70, 70));
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxPanel *headerPanel = new wxPanel(mainPanel);
    headerPanel->SetBackgroundColour(wxColour(0, 102, 204));
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *headerTitle = new wxStaticText(headerPanel, wxID_ANY, "Exam Dashboard System");
    headerTitle->SetForegroundColour(*wxWHITE);
    headerTitle->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    headerSizer->Add(headerTitle, 0, wxALIGN_CENTER_VERTICAL | wxALL, 15);
    headerSizer->AddStretchSpacer();

    wxButton *logoutBtn = new wxButton(headerPanel, wxID_ANY, "Logout", wxDefaultPosition, wxSize(100, 35), wxBORDER_NONE);
    logoutBtn->SetCursor(wxCursor(wxCURSOR_HAND));
    logoutBtn->SetBackgroundColour(wxColour(220, 20, 60));
    logoutBtn->SetForegroundColour(*wxWHITE);
    logoutBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnLogout, this);
    headerSizer->Add(logoutBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);

    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    m_notebook = new wxNotebook(mainPanel, wxID_ANY);
    m_notebook->AddPage(CreateDashboardPage(), "Dashboard");
    mainSizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

    mainPanel->SetSizer(mainSizer);
    Center();
}

wxPanel *AdminFrame::CreateDashboardPage()
{
    wxPanel *panel = new wxPanel(m_notebook);
    panel->SetBackgroundColour(wxColour(70, 70, 70));
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxButton *addBtn = new wxButton(panel, wxID_ANY, " + Add Question ", wxDefaultPosition, wxSize(180, 40), wxBORDER_NONE);
    addBtn->SetCursor(wxCursor(wxCURSOR_HAND));
    addBtn->SetBackgroundColour(wxColour(35, 140, 35));
    addBtn->SetForegroundColour(*wxWHITE);
    addBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnAddQuestions, this);
    sizer->Add(addBtn, 0, wxALL, 20);

    m_questionsPanel = new wxScrolledWindow(panel, wxID_ANY);
    m_questionsPanel->SetScrollRate(0, 20);
    m_questionsTableSizer = new wxBoxSizer(wxVERTICAL);
    m_questionsPanel->SetSizer(m_questionsTableSizer);
    sizer->Add(m_questionsPanel, 1, wxEXPAND | wxLEFT | wxRIGHT, 20);

    wxPanel *pagPanel = new wxPanel(panel);
    pagPanel->SetBackgroundColour(wxColour(70, 70, 70));
    wxBoxSizer *pagSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *prevBtn = new wxButton(pagPanel, wxID_ANY, "< Previous", wxDefaultPosition, wxSize(100, 30));
    prevBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnPagePrev, this);
    prevBtn->SetCursor(wxCursor(wxCURSOR_HAND));

    wxButton *nextBtn = new wxButton(pagPanel, wxID_ANY, "Next >", wxDefaultPosition, wxSize(100, 30));
    nextBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnPageNext, this);
    nextBtn->SetCursor(wxCursor(wxCURSOR_HAND));

    m_pageLabel = new wxStaticText(pagPanel, wxID_ANY, "Page 1");
    m_pageLabel->SetForegroundColour(*wxWHITE);

    pagSizer->Add(prevBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    pagSizer->Add(m_pageLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    pagSizer->Add(nextBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    pagPanel->SetSizer(pagSizer);
    sizer->Add(pagPanel, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    panel->SetSizer(sizer);
    RefreshQuestionsTable();
    return panel;
}

void AdminFrame::RefreshQuestionsTable()
{
    m_questionsTableSizer->Clear(true);

    int start = (m_currentPage - 1) * QUESTIONS_PER_PAGE;
    int end = std::min(start + QUESTIONS_PER_PAGE, (int)m_questions.size());

    for (int i = start; i < end; i++)
    {
        wxPanel *row = new wxPanel(m_questionsPanel, wxID_ANY);
        row->SetBackgroundColour(i % 2 == 0 ? wxColour(55, 55, 55) : wxColour(65, 65, 65));

        wxBoxSizer *rowSizer = new wxBoxSizer(wxHORIZONTAL);
        rowSizer->Add(new wxStaticText(row, wxID_ANY, wxString::Format("%d- %s", i + 1, m_questions[i].getText())), 1, wxALL | wxCENTER, 10);

        wxButton *e = new wxButton(row, wxID_ANY, "Edit", wxDefaultPosition, wxSize(60, 25));
        wxButton *d = new wxButton(row, wxID_ANY, "Delete", wxDefaultPosition, wxSize(60, 25));
        e->Bind(wxEVT_BUTTON, [this, i](wxCommandEvent &)
                { OnEditQuestionAtIndex(i); });
        e->SetCursor(wxCursor(wxCURSOR_HAND));
        d->Bind(wxEVT_BUTTON, [this, i](wxCommandEvent &)
                { OnDeleteQuestionAtIndex(i); });
        d->SetCursor(wxCursor(wxCURSOR_HAND));
        rowSizer->Add(e, 0, wxALL, 5);
        rowSizer->Add(d, 0, wxALL, 5);
        row->SetSizer(rowSizer);
        m_questionsTableSizer->Add(row, 0, wxEXPAND | wxBOTTOM, 2);
    }

    m_pageLabel->SetLabel(wxString::Format("Page %d", m_currentPage));
    m_questionsPanel->Layout();
    m_questionsPanel->FitInside();
}
void AdminFrame::OnExit(wxCommandEvent &event) { Close(); }
void AdminFrame::LoadQuestionsFromDatabase() { m_questions.clear(); }
void AdminFrame::SaveQuestionToDatabase(const Question &q) {}
void AdminFrame::UpdateQuestionInDatabase(int index, const Question &q) {}
void AdminFrame::DeleteQuestionFromDatabase(int index) {}

AddQuestionDialog::AddQuestionDialog(wxWindow *parent, const wxString &title)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(450, 550))
{
    this->SetBackgroundColour(wxColour(60, 60, 60));
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *labelQ = new wxStaticText(this, wxID_ANY, "Question Text:");
    labelQ->SetForegroundColour(*wxWHITE);
    mainSizer->Add(labelQ, 0, wxALL, 10);

    qInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 80), wxTE_MULTILINE);
    mainSizer->Add(qInput, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    wxFlexGridSizer *gridSizer = new wxFlexGridSizer(2, 10, 10);
    gridSizer->AddGrowableCol(1);

    for (int i = 0; i < 4; i++)
    {
        wxStaticText *labelC = new wxStaticText(this, wxID_ANY, wxString::Format("Choice %d:", i + 1));
        labelC->SetForegroundColour(wxColour(200, 200, 200));
        gridSizer->Add(labelC, 0, wxALIGN_CENTER_VERTICAL);

        choices[i] = new wxTextCtrl(this, wxID_ANY, "");
        gridSizer->Add(choices[i], 1, wxEXPAND);
    }
    mainSizer->Add(gridSizer, 0, wxEXPAND | wxALL, 10);

    wxStaticText *labelA = new wxStaticText(this, wxID_ANY, "Correct Answer (1-4):");
    labelA->SetForegroundColour(*wxWHITE);
    mainSizer->Add(labelA, 0, wxLEFT | wxTOP, 10);

    correctAns = new wxChoice(this, wxID_ANY);
    for (int i = 1; i <= 4; i++)
        correctAns->Append(wxString::Format("%d", i));
    correctAns->SetSelection(0);
    mainSizer->Add(correctAns, 0, wxLEFT | wxTOP, 5);

    mainSizer->AddStretchSpacer();
    mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_RIGHT | wxALL, 15);

    SetSizer(mainSizer);
}

void AdminFrame::OnAddQuestions(wxCommandEvent &event)
{
    AddQuestionDialog dlg(this);
    if (dlg.ShowModal() == wxID_OK)
    {
        Question q;
        q.setText(dlg.qInput->GetValue().ToStdString());
        Question::Choice choices;
        for (int i = 0; i < 4; i++)
            choices.push_back(dlg.choices[i]->GetValue().ToStdString());
        q.setChoice(choices);
        q.setCorrect(dlg.correctAns->GetSelection());
        q.setID(m_questions.size() + 1);

        m_questions.push_back(q);
        SaveQuestionToDatabase(q);

        int total = (int)m_questions.size();
        int totalPages = (total + QUESTIONS_PER_PAGE - 1) / QUESTIONS_PER_PAGE;

        m_currentPage = totalPages;

        RefreshQuestionsTable();
    }
}

void AdminFrame::OnEditQuestionAtIndex(int index)
{
    if (index < 0 || index >= (int)m_questions.size())
        return;

    Question &q = m_questions[index];
    AddQuestionDialog dlg(this, "Edit Question");
    dlg.qInput->SetValue(q.getText());

    const auto &currentChoices = q.getChoice();
    for (int i = 0; i < 4; i++)
    {
        if (i < (int)currentChoices.size())
        {
            dlg.choices[i]->SetValue(currentChoices[i]);
        }
    }
    dlg.correctAns->SetSelection(q.getCorrect());

    if (dlg.ShowModal() == wxID_OK)
    {
        q.setText(dlg.qInput->GetValue().ToStdString());

        Question::Choice newChoices;
        for (int i = 0; i < 4; i++)
        {
            newChoices.push_back(dlg.choices[i]->GetValue().ToStdString());
        }
        q.setChoice(newChoices);
        q.setCorrect(dlg.correctAns->GetSelection());

        UpdateQuestionInDatabase(index, q);
        RefreshQuestionsTable();
        wxMessageBox("Question updated!", "Success", wxOK | wxICON_INFORMATION);
    }
}
void AdminFrame::OnDeleteQuestionAtIndex(int index)
{
    if (wxMessageBox("Delete this question?", "Confirm", wxYES_NO) == wxYES)
    {
        m_questions.erase(m_questions.begin() + index);
        RefreshQuestionsTable();
    }
}

void AdminFrame::OnLogout(wxCommandEvent &event)
{
    Close();
}

void AdminFrame::OnPagePrev(wxCommandEvent &event)
{
    if (m_currentPage > 1)
    {
        m_currentPage--;
        RefreshQuestionsTable();
    }
}
void AdminFrame::OnPageNext(wxCommandEvent &event)
{
    int total = (int)m_questions.size();
    int totalPages = total == 0 ? 1 : (total + QUESTIONS_PER_PAGE - 1) / QUESTIONS_PER_PAGE;
    if (m_currentPage < totalPages)
    {
        m_currentPage++;
        RefreshQuestionsTable();
    }
}
AdminFrame::~AdminFrame() {}
