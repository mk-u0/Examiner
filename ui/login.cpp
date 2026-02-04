#include <login.h>

LoginFrame::LoginFrame(bool show) : wxFrame(nullptr, wxID_ANY, "Hello World") {
    if (show) {
        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");
    }
}
