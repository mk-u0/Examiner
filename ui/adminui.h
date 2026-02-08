#ifndef ADMINUI_H
#define ADMINUI_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/scrolwin.h> 
#include <vector>
#include <exam.h> 


class AddQuestionDialog : public wxDialog {
public:
    wxTextCtrl* qInput;
    wxTextCtrl* choices[4];
    wxChoice* correctAns;

    AddQuestionDialog(wxWindow *parent, const wxString &title = "Add New Question");
};
class AdminFrame : public wxFrame {
public:
    AdminFrame(const wxString &username);
    virtual ~AdminFrame(); 

private:

    void OnAddQuestions(wxCommandEvent &event);
    void RefreshQuestionsTable();
    void OnExit(wxCommandEvent &event);
    void OnLogout(wxCommandEvent &event);
    void OnPagePrev(wxCommandEvent &event);
    void OnPageNext(wxCommandEvent &event);
    void OnEditQuestionAtIndex(int index);
    void OnDeleteQuestionAtIndex(int index);

    void LoadQuestionsFromDatabase();
    void SaveQuestionToDatabase(const Question &q);
    void UpdateQuestionInDatabase(int index, const Question &q);
    void DeleteQuestionFromDatabase(int index);

    wxPanel* CreateDashboardPage();

    wxString m_username;
    std::vector<Question> m_questions; 
    
    wxNotebook* m_notebook;
    wxScrolledWindow* m_questionsPanel;
    wxBoxSizer* m_questionsTableSizer;
    wxStaticText* m_pageLabel;
    
    int m_currentPage; 
    static const int QUESTIONS_PER_PAGE = 5; 

    wxDECLARE_EVENT_TABLE();
};

#endif