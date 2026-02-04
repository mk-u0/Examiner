#include <user.h>
#include <dataio.h>
#include <wx/wx.h>
#include <login.h>

class StudentApp : public wxApp {
public:
    bool OnInit() override;
};
 
// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(StudentApp);

bool StudentApp::OnInit() {
    DataIO io("data.db");
    io.create_table();

    Student stu{"mk", "12345678"};
    bool match = stu.verifyPassword("12345678");
    LoginFrame *frame = new LoginFrame(match);
    frame->Show();
    return true;
}
