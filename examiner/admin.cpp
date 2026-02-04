#include <user.h>
#include <dataio.h>
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    bool OnInit() override;
};
 
// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
public:
    MyFrame(bool show);
};

bool MyApp::OnInit() {
    DataIO io;
    io.init();
    
    User u{"mk", "12345678"};
    bool match = u.verify_pass("12345678");
    MyFrame *frame = new MyFrame(match);
    frame->Show();
    return true;
}

MyFrame::MyFrame(bool show) : wxFrame(nullptr, wxID_ANY, "Hello World") {
    if (show) {
        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");
    }
}
