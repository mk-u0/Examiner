#include "adminui.h"
#include "login.h"
#include <wx/numdlg.h>

wxBEGIN_EVENT_TABLE(AdminFrame, wxFrame)
    EVT_MENU(wxID_EXIT, AdminFrame::OnExit)
        wxEND_EVENT_TABLE()

            AdminFrame::AdminFrame(const wxString &username)
    : wxFrame(nullptr, wxID_ANY, "Exam Dashboard - " + username,
              wxDefaultPosition, wxSize(1024, 768)),
      m_username(username),
      m_questionsPanel(nullptr),
      m_questionsTableSizer(nullptr),
      m_pageLabel(nullptr),
      m_currentPage(1)
{
    // it will change to conect db
    LoadQuestionsFromDatabase();

    CreateStatusBar();
    SetStatusText("Welcome, " + username + "! | Exam Dashboard System");

    // Main
    wxPanel *mainPanel = new wxPanel(this);
    mainPanel->SetBackgroundColour(wxColour(70, 70, 70));
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Header
    wxPanel *headerPanel = new wxPanel(mainPanel);
    headerPanel->SetBackgroundColour(wxColour(0, 102, 204));
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *headerTitle = new wxStaticText(headerPanel, wxID_ANY, "Exam Dashboard System");
    headerTitle->SetForegroundColour(*wxWHITE);
    headerTitle->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    headerSizer->Add(headerTitle, 0, wxALIGN_CENTER_VERTICAL | wxALL, 15);
    headerSizer->AddStretchSpacer();

    wxStaticText *userLabel = new wxStaticText(headerPanel, wxID_ANY, "User: " + username);
    userLabel->SetForegroundColour(*wxWHITE);
    userLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    headerSizer->Add(userLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 15);

    // Logout Button
    wxButton *logoutBtn = new wxButton(headerPanel, wxID_ANY, "Logout", wxDefaultPosition, wxSize(100, 35), wxBORDER_NONE);
    logoutBtn->SetBackgroundColour(wxColour(220, 20, 60));
    logoutBtn->SetForegroundColour(*wxWHITE);
    logoutBtn->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    logoutBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnLogout, this);
    logoutBtn->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent &event)
                    {
        logoutBtn->SetCursor(wxCursor(wxCURSOR_HAND)); // hand
        logoutBtn->SetBackgroundColour(wxColour(255, 69, 0));
        logoutBtn->Refresh(); });

    logoutBtn->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent &event)
                    {
        logoutBtn->SetCursor(wxCursor(wxCURSOR_ARROW));
        logoutBtn->SetBackgroundColour(wxColour(220, 20, 60));
        logoutBtn->Refresh(); });

    headerSizer->Add(logoutBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);
    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    // Notebook
    m_notebook = new wxNotebook(mainPanel, wxID_ANY);
    m_notebook->AddPage(CreateDashboardPage(), "Dashboard");
    mainSizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);

    mainPanel->SetSizer(mainSizer);
    Center();
}

// Dashboard Page
wxPanel *AdminFrame::CreateDashboardPage()
{
    wxPanel *panel = new wxPanel(m_notebook);
    panel->SetBackgroundColour(wxColour(70, 70, 70));
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    // Welcome
    wxStaticText *welcome = new wxStaticText(panel, wxID_ANY, "Hello " + m_username + ", Welcome to Exam Dashboard");
    welcome->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    welcome->SetForegroundColour(wxColour(30, 144, 255));
    sizer->Add(welcome, 0, wxLEFT | wxTOP, 20);
    sizer->AddSpacer(10);

    // Add button
    wxButton *addBtn = new wxButton(panel, wxID_ANY, " + Add Question ", wxDefaultPosition, wxSize(180, 40), wxBORDER_NONE);
    addBtn->SetBackgroundColour(wxColour(35, 140, 35));
    addBtn->SetForegroundColour(*wxWHITE);
    addBtn->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    addBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnAddQuestions, this);
    addBtn->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent &)
                 {
        addBtn->SetBackgroundColour(wxColour(50, 160, 50));
        addBtn->SetCursor(wxCursor(wxCURSOR_HAND));
        addBtn->Refresh(); });
    addBtn->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent &)
                 {
        addBtn->SetBackgroundColour(wxColour(34, 139, 34));
        addBtn->SetCursor(wxCursor(wxCURSOR_ARROW));
        addBtn->Refresh(); });
    sizer->Add(addBtn, 0, wxLEFT | wxBOTTOM, 20);
    sizer->AddSpacer(5);

    // Table header row
    wxPanel *headerRow = new wxPanel(panel);
    headerRow->SetBackgroundColour(wxColour(50, 50, 50));
    wxBoxSizer *headerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *colNum = new wxStaticText(headerRow, wxID_ANY, " # ");
    wxStaticText *colQ = new wxStaticText(headerRow, wxID_ANY, " Question ");
    wxStaticText *colActs = new wxStaticText(headerRow, wxID_ANY, " Edit | Delete ");
    colNum->SetForegroundColour(wxColour(200, 200, 200));
    colQ->SetForegroundColour(wxColour(200, 200, 200));
    colActs->SetForegroundColour(wxColour(200, 200, 200));
    colNum->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    colQ->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    colActs->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    headerSizer->Add(colNum, 0, wxALL, 10);
    headerSizer->Add(colQ, 1, wxALL | wxEXPAND, 10);
    headerSizer->Add(colActs, 0, wxALL, 10);
    headerRow->SetSizer(headerSizer);
    sizer->Add(headerRow, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);

    // Pagination
    wxPanel *paginationPanel = new wxPanel(panel);
    paginationPanel->SetBackgroundColour(wxColour(70, 70, 70));
    wxBoxSizer *pagSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton *prevBtn = new wxButton(paginationPanel, wxID_ANY, " << Prev ", wxDefaultPosition, wxSize(90, 32), wxBORDER_NONE);
    m_pageLabel = new wxStaticText(paginationPanel, wxID_ANY, "Page 1 of 1");
    wxButton *nextBtn = new wxButton(paginationPanel, wxID_ANY, " Next >> ", wxDefaultPosition, wxSize(90, 32), wxBORDER_NONE);

    prevBtn->SetBackgroundColour(wxColour(30, 144, 255));
    prevBtn->SetForegroundColour(*wxWHITE);
    nextBtn->SetBackgroundColour(wxColour(30, 144, 255));
    nextBtn->SetForegroundColour(*wxWHITE);
    m_pageLabel->SetForegroundColour(wxColour(220, 220, 220));
    m_pageLabel->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    prevBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnPagePrev, this);
    nextBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnPageNext, this);
    for (wxButton *b : {prevBtn, nextBtn})
    {
        b->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent &)
                { b->SetCursor(wxCursor(wxCURSOR_HAND)); b->SetBackgroundColour(wxColour(65, 105, 225)); b->Refresh(); });
        b->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent &)
                { b->SetCursor(wxCursor(wxCURSOR_ARROW)); b->SetBackgroundColour(wxColour(30, 144, 255)); b->Refresh(); });
    }

    pagSizer->AddStretchSpacer();
    pagSizer->Add(prevBtn, 0, wxRIGHT, 15);
    pagSizer->Add(m_pageLabel, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 15);
    pagSizer->Add(nextBtn, 0, wxLEFT, 15);
    pagSizer->AddStretchSpacer();
    paginationPanel->SetSizer(pagSizer);
    sizer->Add(paginationPanel, 0, wxEXPAND | wxBOTTOM, 15);

    panel->SetSizer(sizer);
    RefreshQuestionsTable();
    return panel;
}

void AdminFrame::RefreshQuestionsTable()
{
    if (!m_questionsTableSizer || !m_questionsPanel)
        return;

    m_questionsTableSizer->Clear(true);

    // will change in db
    LoadQuestionsFromDatabase();

    int total = (int)m_questions.size();
    int totalPages = total == 0 ? 1 : (total + QUESTIONS_PER_PAGE - 1) / QUESTIONS_PER_PAGE;
    if (m_currentPage > totalPages)
        m_currentPage = totalPages;
    if (m_currentPage < 1)
        m_currentPage = 1;

    int start = (m_currentPage - 1) * QUESTIONS_PER_PAGE;
    int end = start + QUESTIONS_PER_PAGE;
    if (end > total)
        end = total;

    for (int i = start; i < end; i++)
    {
        int globalIndex = i;
        wxPanel *row = new wxPanel(m_questionsPanel, wxID_ANY);
        row->SetBackgroundColour((i - start) % 2 == 0 ? wxColour(55, 55, 55) : wxColour(65, 65, 65));
        wxBoxSizer *rowSizer = new wxBoxSizer(wxHORIZONTAL);

        wxString numStr = wxString::Format(" %d ", globalIndex + 1);
        wxStaticText *numLabel = new wxStaticText(row, wxID_ANY, numStr);
        numLabel->SetForegroundColour(wxColour(180, 180, 180));
        numLabel->SetMinSize(wxSize(40, -1));

        wxString qText = wxString(m_questions[globalIndex].getText());
        if (qText.Length() > 80)
            qText = qText.Left(77) + "...";
        wxStaticText *qLabel = new wxStaticText(row, wxID_ANY, " " + qText + " ", wxDefaultPosition, wxDefaultSize, wxST_ELLIPSIZE_END);
        qLabel->SetForegroundColour(wxColour(230, 230, 230));
        qLabel->SetMinSize(wxSize(200, -1));

        wxButton *editBtn = new wxButton(row, wxID_ANY, "Edit", wxDefaultPosition, wxSize(60, 28), wxBORDER_NONE);
        wxButton *delBtn = new wxButton(row, wxID_ANY, "Delete", wxDefaultPosition, wxSize(60, 28), wxBORDER_NONE);

        editBtn->SetBackgroundColour(wxColour(70, 130, 180));
        delBtn->SetBackgroundColour(wxColour(178, 34, 34));
        for (wxButton *btn : {editBtn, delBtn})
        {
            btn->SetForegroundColour(*wxWHITE);
            btn->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            btn->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent &)
                      { btn->SetCursor(wxCursor(wxCURSOR_HAND)); btn->Refresh(); });
            btn->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent &)
                      { btn->SetCursor(wxCursor(wxCURSOR_ARROW)); btn->Refresh(); });
        }
        editBtn->Bind(wxEVT_BUTTON, [this, globalIndex](wxCommandEvent &)
                      { OnEditQuestionAtIndex(globalIndex); });
        delBtn->Bind(wxEVT_BUTTON, [this, globalIndex](wxCommandEvent &)
                     { OnDeleteQuestionAtIndex(globalIndex); });

        rowSizer->Add(numLabel, 0, wxALL, 8);
        rowSizer->Add(qLabel, 1, wxALL | wxEXPAND, 8);
        rowSizer->Add(editBtn, 0, wxALL, 5);
        rowSizer->Add(delBtn, 0, wxALL, 5);
        row->SetSizer(rowSizer);
        m_questionsTableSizer->Add(row, 0, wxEXPAND);
    }

    m_pageLabel->SetLabel(wxString::Format("Page %d of %d", m_currentPage, totalPages));
    m_questionsPanel->Layout();
    m_questionsPanel->FitInside();
}

// Event Handlers
void AdminFrame::OnLogout(wxCommandEvent &event)
{
    if (wxMessageBox("Are you sure you want to logout?", "Confirm Logout",
                     wxYES_NO | wxICON_QUESTION, this) == wxYES)
    {
        Close();
    }
}

void AdminFrame::OnExit(wxCommandEvent &event)
{
    Close();
}
// will change in db
void AdminFrame::LoadQuestionsFromDatabase()
{
    m_questions.clear();
    // will change in db
}
void AdminFrame::SaveQuestionToDatabase(const Question &q)
{
    // will change in db
}
void AdminFrame::UpdateQuestionInDatabase(int index, const Question &q)
{
    // will change in db
}

void AdminFrame::DeleteQuestionFromDatabase(int index)
{
    // will change in db
}

void AdminFrame::OnAddQuestions(wxCommandEvent &event)
{
    wxTextEntryDialog dlgText(this, "Enter the question text:", "Add New Question");
    if (dlgText.ShowModal() != wxID_OK)
        return;

    Question q;
    wxString qText = dlgText.GetValue().Trim();
    if (qText.IsEmpty())
    {
        wxMessageBox("Question text cannot be empty.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    q.setText(qText.ToStdString());

    const char *prompts[] = {"Choice 1:", "Choice 2:", "Choice 3:", "Choice 4:"};
    Question::Choice choices;
    for (int i = 0; i < 4; i++)
    {
        wxTextEntryDialog dlg(this, prompts[i], "Add Choices", "");
        if (dlg.ShowModal() != wxID_OK)
            return;
        choices.push_back(dlg.GetValue().Trim().ToStdString());
    }
    q.setChoice(choices);

    wxNumberEntryDialog dlgCorrect(this, "Which choice is correct? (1-4)", "Correct answer", "Correct choice", 1, 1, 4);
    if (dlgCorrect.ShowModal() != wxID_OK)
        return;
    unsigned correctIdx = (unsigned)dlgCorrect.GetValue() - 1;
    if (correctIdx > 3)
        correctIdx = 3;
    q.setCorrect(correctIdx);

    m_questions.push_back(q);
    SaveQuestionToDatabase(q);
    wxMessageBox("Question added successfully!", "Success", wxOK | wxICON_INFORMATION);
    RefreshQuestionsTable();
}

void AdminFrame::OnEditQuestionAtIndex(int index)
{
    if (index < 0 || index >= (int)m_questions.size())
        return;

    Question &q = m_questions[index];

    wxTextEntryDialog dlgText(this, "Edit question text:", "Edit Question", wxString(q.getText()));
    if (dlgText.ShowModal() != wxID_OK)
        return;
    q.setText(dlgText.GetValue().Trim().ToStdString());

    const Question::Choice &currentChoices = q.getChoice();
    const char *prompts[] = {"Choice 1:", "Choice 2:", "Choice 3:", "Choice 4:"};
    Question::Choice choices;
    for (int i = 0; i < 4; i++)
    {
        wxString defaultVal = (i < (int)currentChoices.size()) ? wxString(currentChoices[i]) : "";
        wxTextEntryDialog dlg(this, prompts[i], "Edit Choices", defaultVal);
        if (dlg.ShowModal() != wxID_OK)
            return;
        choices.push_back(dlg.GetValue().Trim().ToStdString());
    }
    q.setChoice(choices);

    wxNumberEntryDialog dlgCorrect(this, "Which choice is correct? (1-4)", "Correct answer", "Correct choice", q.getCorrect() + 1, 1, 4);
    if (dlgCorrect.ShowModal() != wxID_OK)
        return;
    unsigned correctIdx = (unsigned)dlgCorrect.GetValue() - 1;
    if (correctIdx > 3)
        correctIdx = 3;
    q.setCorrect(correctIdx);

    UpdateQuestionInDatabase(index, q);
    wxMessageBox("Question updated successfully!", "Success", wxOK | wxICON_INFORMATION);
    RefreshQuestionsTable();
}

void AdminFrame::OnDeleteQuestionAtIndex(int index)
{
    if (index < 0 || index >= (int)m_questions.size())
        return;

    if (wxMessageBox("Are you sure you want to delete this question?", "Confirm Delete", wxYES_NO | wxICON_WARNING) != wxYES)
        return;

    DeleteQuestionFromDatabase(index);
    m_questions.erase(m_questions.begin() + index);
    wxMessageBox("Question deleted successfully!", "Success", wxOK | wxICON_INFORMATION);
    RefreshQuestionsTable();
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
