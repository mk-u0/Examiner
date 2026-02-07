#include "studentui.h"
#include <fstream>
#include "../core/exam.h"
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/radiobut.h>

StudentFrame::StudentFrame(const wxString &username)
    : wxFrame(nullptr, wxID_ANY, "Student Dashboard - " + username,
              wxDefaultPosition, wxSize(750, 600)),
      m_username(username)
{
    m_panel = new wxPanel(this);
    m_panel->SetBackgroundColour(wxColour(70, 70, 70));
    m_sizer = new wxBoxSizer(wxVERTICAL);

    m_welcomeText = new wxStaticText(m_panel, wxID_ANY, "Welcome, " + username + "!");
    m_welcomeText->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    m_welcomeText->SetForegroundColour(wxColour(30, 144, 255));
    m_sizer->Add(m_welcomeText, 0, wxALIGN_CENTER | wxTOP, 20);
    m_sizer->AddSpacer(50);

    m_startExamBtn = new wxButton(m_panel, wxID_ANY, "Start Exam", wxDefaultPosition, wxSize(200, 40), wxBORDER_NONE);
    m_startExamBtn->SetBackgroundColour(wxColour(30, 144, 255));
    m_startExamBtn->SetForegroundColour(*wxWHITE);
    m_startExamBtn->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    m_sizer->Add(m_startExamBtn, 0, wxALIGN_CENTER | wxTOP, 30);
    m_sizer->AddSpacer(50);

    m_viewResultsBtn = new wxButton(m_panel, wxID_ANY, "View Results", wxDefaultPosition, wxSize(200, 40), wxBORDER_NONE);
    m_viewResultsBtn->SetBackgroundColour(wxColour(30, 144, 255));
    m_viewResultsBtn->SetForegroundColour(*wxWHITE);
    m_viewResultsBtn->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    m_sizer->Add(m_viewResultsBtn, 0, wxALIGN_CENTER | wxTOP, 30);

    m_panel->SetSizer(m_sizer);
    LoadQuestions();

    m_startExamBtn->Bind(wxEVT_BUTTON, &StudentFrame::OnStartExam, this);
    m_viewResultsBtn->Bind(wxEVT_BUTTON, &StudentFrame::OnViewResults, this);

    auto SetupButtonHover = [](wxButton *btn)
    {
        btn->Bind(wxEVT_ENTER_WINDOW, [btn](wxMouseEvent &)
                  {
            btn->SetBackgroundColour(wxColour(65, 105, 225));
            btn->SetCursor(wxCursor(wxCURSOR_HAND));
            btn->Refresh(); });
        btn->Bind(wxEVT_LEAVE_WINDOW, [btn](wxMouseEvent &)
                  {
            btn->SetBackgroundColour(wxColour(30, 144, 255));
            btn->SetCursor(wxCursor(wxCURSOR_ARROW));
            btn->Refresh(); });
    };
    SetupButtonHover(m_startExamBtn);
    SetupButtonHover(m_viewResultsBtn);
    Center();
}

void StudentFrame::LoadQuestions() // db
{
    m_questions.clear();
    // Db
}

void StudentFrame::SetExamAnswers(const std::vector<int> &answers)
{
    m_answers = answers;
}

void StudentFrame::OnStartExam(wxCommandEvent &event)
{
    LoadQuestions();
    if (m_questions.empty())
    {
        wxMessageBox("No questions available!", "Info", wxOK | wxICON_INFORMATION);
        return;
    }

    wxDialog *examDlg = new wxDialog(this, wxID_ANY, "Exam", wxDefaultPosition, wxSize(700, 550),
                                     wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX);
    examDlg->SetBackgroundColour(wxColour(60, 60, 60));

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *title = new wxStaticText(examDlg, wxID_ANY, "Answer all questions, then click Submit.");
    title->SetForegroundColour(wxColour(220, 220, 220));
    title->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    topSizer->Add(title, 0, wxALL, 10);

    std::vector<wxRadioButton *> radios;
    radios.reserve(m_questions.size() * 4);

    for (size_t i = 0; i < m_questions.size(); i++)
    {
        const Question &q = m_questions[i];
        wxPanel *qPanel = new wxPanel(examDlg, wxID_ANY);
        qPanel->SetBackgroundColour(wxColour(65, 65, 65));
        wxBoxSizer *qSizer = new wxBoxSizer(wxVERTICAL);

        wxString qLabel = wxString::Format("Q%d: ", (int)(i + 1)) + q.getText();
        wxStaticText *qText = new wxStaticText(qPanel, wxID_ANY, qLabel);
        qText->SetForegroundColour(wxColour(240, 240, 240));
        qText->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        qText->Wrap(600);
        qSizer->Add(qText, 0, wxALL, 8);

        wxPanel *choicesPanel = new wxPanel(qPanel, wxID_ANY);
        choicesPanel->SetBackgroundColour(wxColour(65, 65, 65));
        wxBoxSizer *choicesSizer = new wxBoxSizer(wxVERTICAL);
        const Question::Choice &choices = q.getChoice();
        for (int j = 0; j < 4; j++)
        {
            wxString choiceText = (j < (int)choices.size()) ? wxString(choices[j]) : "";
            wxRadioButton *rb = new wxRadioButton(choicesPanel, wxID_ANY, "  " + choiceText,
                                                  wxDefaultPosition, wxDefaultSize, (j == 0 ? wxRB_GROUP : 0));
            rb->SetForegroundColour(wxColour(220, 220, 220));
            rb->SetBackgroundColour(wxColour(65, 65, 65));
            rb->SetCursor(wxCursor(wxCURSOR_HAND));
            choicesSizer->Add(rb, 0, wxLEFT | wxBOTTOM, 6);
            radios.push_back(rb);
        }
        choicesPanel->SetSizer(choicesSizer);
        qSizer->Add(choicesPanel, 0, wxLEFT, 20);
        qPanel->SetSizer(qSizer);
        topSizer->Add(qPanel, 0, wxEXPAND | wxALL, 5);
    }

    wxButton *submitBtn = new wxButton(examDlg, wxID_ANY, "Submit Exam", wxDefaultPosition, wxSize(140, 36), wxBORDER_NONE);
    submitBtn->SetBackgroundColour(wxColour(34, 139, 34));
    submitBtn->SetForegroundColour(*wxWHITE);
    submitBtn->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    submitBtn->SetCursor(wxCursor(wxCURSOR_HAND));

    submitBtn->Bind(wxEVT_BUTTON, [this, examDlg, &radios](wxCommandEvent &)
                    {
        std::vector<int> answers;
        answers.reserve(m_questions.size());
        for (size_t i = 0; i < m_questions.size(); i++)
        {
            int selected = -1;
            for (int j = 0; j < 4; j++)
            {
                if (radios[i * 4 + j]->GetValue())
                {
                    selected = j;
                    break;
                }
            }
            answers.push_back(selected);
        }
        SetExamAnswers(answers);
        examDlg->EndModal(wxID_OK); });

    topSizer->Add(submitBtn, 0, wxALIGN_CENTER | wxALL, 15);
    examDlg->SetSizer(topSizer);

    if (examDlg->ShowModal() == wxID_OK)
    {
        int score = 0;
        for (size_t i = 0; i < m_questions.size() && i < m_answers.size(); i++)
            if (m_answers[i] >= 0 && m_answers[i] == (int)m_questions[i].getCorrect())
                score++;
        wxString msg = wxString::Format("Your Score: %d / %lu", score, m_questions.size());
        wxMessageBox(msg, "Exam Result", wxOK | wxICON_INFORMATION);
    }

    examDlg->Destroy();
}

void StudentFrame::OnViewResults(wxCommandEvent &event)
{
    if (m_answers.empty())
    {
        wxMessageBox("You have not taken the exam yet! Click Start Exam first.", "Info", wxOK | wxICON_INFORMATION);
        return;
    }
    int score = 0;
    for (size_t i = 0; i < m_questions.size() && i < m_answers.size(); i++)
        if (m_answers[i] >= 0 && m_answers[i] == (int)m_questions[i].getCorrect())
            score++;
    wxString msg = wxString::Format("Your Score: %d / %lu", score, m_questions.size());
    wxMessageBox(msg, "Exam Result", wxOK | wxICON_INFORMATION);
}

StudentFrame::~StudentFrame() {}
