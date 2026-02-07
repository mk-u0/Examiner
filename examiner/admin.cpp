#include <user.h>
#include <dataio.h>
#include <wx/wx.h>
#include <login.h>
#include "../ui/adminui.h"

class AdminApp : public wxApp
{
public:
    bool OnInit() override;
};

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
// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(AdminApp);

bool AdminApp::OnInit()
{
    DataIO io("data.db");
    io.init();

    int test_rc = io.deleteStudent(999);

    if (test_rc == SQLITE_DONE || test_rc == SQLITE_OK)
    {
        wxLogMessage("Logic Check: Delete command executed successfully!");
    }
    else
    {
        wxLogMessage("Logic Check: Something is wrong. Error Code: %d", test_rc);
    }

    Admin admin("admin", "admin");
    io.addAdmin(admin);
    admin = io.getAdminByUser("admin");
    bool match = admin.verifyPassword("admin");
    globalLoginFrame = new LoginFrame();
    globalLoginFrame->setCallback(Auth);
    globalLoginFrame->Show();

    return true;
}
