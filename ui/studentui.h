#pragma once
#include <wx/wx.h>
#include <exam.h>
#include <dataio.h>
#include <vector>

class StudentFrame : public wxFrame
{
public:
    StudentFrame(const wxString &username);
    ~StudentFrame();

private:
    DataIO *db;
    wxPanel *m_panel;
    wxBoxSizer *m_sizer;
    wxStaticText *m_welcomeText;
    wxButton *m_startExamBtn;
    wxButton *m_viewResultsBtn;

    wxString m_username;
    std::vector<Question> m_questions;
    std::vector<int> m_answers;

    void LoadQuestions();
    void OnStartExam(wxCommandEvent &event);
    void OnViewResults(wxCommandEvent &event);
    void SetExamAnswers(const std::vector<int> &answers);
};
