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
    io.create_table();

    User u{"mk", "12345678"};
    bool match = u.verify_pass("12345678");
    LoginFrame *frame = new LoginFrame(match);
    frame->Show();
    return true;
}
