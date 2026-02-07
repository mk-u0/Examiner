#ifndef ADMINUI_H
#define ADMINUI_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <vector>
#include "../core/exam.h"

static const int QUESTIONS_PER_PAGE = 5;

class AdminFrame : public wxFrame
{
public:
    AdminFrame(const wxString &username);
    virtual ~AdminFrame();

private:
    wxString m_username;
    wxNotebook *m_notebook;
    wxPanel *m_questionsPanel;
    wxBoxSizer *m_questionsTableSizer;
    wxStaticText *m_pageLabel;
    int m_currentPage;

    wxPanel *CreateDashboardPage();
    void RefreshQuestionsTable();

    std::vector<Question> m_questions;

    void OnLogout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAddQuestions(wxCommandEvent &event);
    void OnPagePrev(wxCommandEvent &event);
    void OnPageNext(wxCommandEvent &event);
    void OnEditQuestionAtIndex(int index);
    void OnDeleteQuestionAtIndex(int index);

    // waiting for db connect
    void LoadQuestionsFromDatabase();
    void SaveQuestionToDatabase(const Question &q);
    void UpdateQuestionInDatabase(int index, const Question &q);
    void DeleteQuestionFromDatabase(int index);

    wxDECLARE_EVENT_TABLE();
};

#endif