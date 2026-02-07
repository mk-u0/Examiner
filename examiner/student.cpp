#include <user.h>
#include <dataio.h>
#include <wx/wx.h>
#include <login.h>
#include "../ui/studentui.h"

class StudentApp : public wxApp
{
public:
    bool OnInit() override;
};

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

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(StudentApp);

bool StudentApp::OnInit()
{
    DataIO io("data.db");
    io.init();

    Student stu{"mk", "12345678"};
    io.addStudent(stu);
    stu = io.getStudentByUser("mk");
    bool match = stu.verifyPassword("12345678");
    globalLoginFrame = new LoginFrame();
    globalLoginFrame->setCallback(Auth);
    globalLoginFrame->Show();
    return true;
}