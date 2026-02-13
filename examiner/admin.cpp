#include <user.h>
#include <dataio.h>
#include <wx/wx.h>
#include <login.h>
#include <adminui.h>


class AdminApp : public wxApp
{
public:
    bool OnInit() override;
};
wxIMPLEMENT_APP(AdminApp);

LoginFrame *globalLoginFrame = nullptr;
void Auth(const char *username, const char *pass)
{
    DataIO io("data.db");
    Admin admin = io.getAdminByUser(username);

    if (admin.getUsername().empty())
    {
        wxMessageBox("User not found!", "Error");
        return;
    }

    if (admin.verifyPassword(pass))
    {
        wxMessageBox("Login Successful!", "Welcome");
        AdminFrame *adminFrame = new AdminFrame(admin.getUsername());
        adminFrame->Show();

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

bool AdminApp::OnInit()
{
    DataIO io("data.db");
    io.init();

    Admin admin("admin", "admin");
    io.addAdmin(admin);
    Exam exam;
    exam.setID(1);
    exam.setDuration(30);
    io.addExam(exam);
    globalLoginFrame = new LoginFrame();
    globalLoginFrame->setCallback(Auth);
    globalLoginFrame->Show();

    return true;
}
