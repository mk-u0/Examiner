#include <user.h>
#include <dataio.h>
#include <wx/wx.h>
#include <login.h>
#include <studentui.h>

class StudentApp : public wxApp
{
public:
    bool OnInit() override;
};
wxIMPLEMENT_APP(StudentApp);

LoginFrame *globalLoginFrame = nullptr;
void Auth(const char *username, const char *pass)
{
    DataIO io("data.db");
    Student student = io.getStudentByUser(username);

    if (student.getUsername().empty())
    {
        wxMessageBox("User not found!", "Error");
        return;
    }

    if (student.verifyPassword(pass))
    {
        wxMessageBox("Login Successful!", "Welcome");
        StudentFrame *studentFrame = new StudentFrame(student.getUsername());
        studentFrame->Show();

        if (globalLoginFrame)
        {

            globalLoginFrame->Close();
        }
    }
    else
    {
        wxMessageBox("Incorrect Password!", "Login Failed");
    }
}

bool StudentApp::OnInit()
{
    DataIO io("data.db");
    io.init();

    Student stu{"mk", "1234"};
    io.addStudent(stu);
    globalLoginFrame = new LoginFrame();
    globalLoginFrame->setCallback(Auth);
    globalLoginFrame->Show();
    return true;
}
