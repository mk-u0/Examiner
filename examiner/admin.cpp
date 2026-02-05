#include <user.h>
#include <dataio.h>
#include <wx/wx.h>
#include <login.h>

class AdminApp : public wxApp {
public:
    bool OnInit() override;
};
 
// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(AdminApp);

bool AdminApp::OnInit() {
    DataIO io("data.db");
    io.init();

    Admin admin{"admin", "admin"};
    io.addAdmin(admin);
    admin = io.getAdminByUser("admin");
    bool match = admin.verifyPassword("admin");
    LoginFrame *frame = new LoginFrame(match);
    frame->Show();
    return true;
}
