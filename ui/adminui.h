#ifndef ADMINUI_H
#define ADMINUI_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/scrolwin.h>
#include <vector>
#include <exam.h>
#include <dataio.h>

class AddQuestionDialog : public wxDialog
{
public:
    wxTextCtrl *qInput;
    wxTextCtrl *choices[4];
    wxChoice *correctAns;

    AddQuestionDialog(wxWindow *parent, const wxString &title = "Add New Question");
};
class AdminFrame : public wxFrame
{
public:
    AdminFrame(const wxString &username);
    virtual ~AdminFrame();

private:
    void OnAddQuestions(wxCommandEvent &event);
    void RefreshQuestionsTable();
    void OnLogout(wxCommandEvent &event);
    void OnPagePrev(wxCommandEvent &event);
    void OnPageNext(wxCommandEvent &event);
    void OnEditQuestionAtIndex(int index);
    void OnDeleteQuestionAtIndex(int index);

    void LoadExam();
    void SaveExam();

    wxPanel *CreateDashboardPage();

    DataIO *db;
    wxString m_username;
    Exam m_exam;

    wxNotebook *m_notebook;
    wxScrolledWindow *m_questionsPanel;
    wxBoxSizer *m_questionsTableSizer;
    wxStaticText *m_pageLabel;

    int m_currentPage;
    static const int QUESTIONS_PER_PAGE = 5;
};

#endif