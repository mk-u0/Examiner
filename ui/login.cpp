#include "login.h"
#include <string>

LoginFrame::LoginFrame()
    : wxFrame(nullptr, wxID_ANY, "Exam Dashboard", wxDefaultPosition, wxSize(500, 600))
{

    wxPanel *panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(70, 70, 70));

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *title = new wxStaticText(panel, wxID_ANY, "Welcome To Exam Portal");
    title->SetFont(wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    title->SetForegroundColour(wxColour(70, 144, 255));
    mainSizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 30);

    wxStaticText *subtitle = new wxStaticText(panel, wxID_ANY, "Login to Continue");
    wxFont subFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    subtitle->SetFont(subFont);
    subtitle->SetForegroundColour(wxColour(100, 130, 180));
    mainSizer->Add(subtitle, 0, wxALIGN_CENTER | wxTOP, 10);

    wxStaticText *emailLabel = new wxStaticText(panel, wxID_ANY, "Email:");
    emailLabel->SetForegroundColour(*wxWHITE);
    mainSizer->Add(emailLabel, 0, wxLEFT | wxTOP, 75);

    emailCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(350, 35));
    emailCtrl->SetFont(wxFont(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    mainSizer->Add(emailCtrl, 0, wxALIGN_CENTER | wxTOP, 5);

    wxStaticText *passLabel = new wxStaticText(panel, wxID_ANY, "Password:");
    passLabel->SetForegroundColour(*wxWHITE);
    mainSizer->Add(passLabel, 0, wxLEFT | wxTOP, 75);

    passCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(350, 35), wxTE_PASSWORD);
    passCtrl->SetFont(wxFont(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    mainSizer->Add(passCtrl, 0, wxALIGN_CENTER | wxTOP, 5);

    mainSizer->AddStretchSpacer(1);

    wxButton *loginBtn = new wxButton(panel, wxID_ANY, "Login", wxDefaultPosition, wxSize(150, 45), wxBORDER_NONE);
    loginBtn->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent &event)
                   { loginBtn->SetCursor(wxCursor(wxCURSOR_HAND)); });

    loginBtn->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent &event)
                   { loginBtn->SetCursor(wxCursor(wxCURSOR_ARROW)); });
    loginBtn->SetBackgroundColour(wxColour(30, 144, 255));
    loginBtn->SetForegroundColour(*wxWHITE);
    loginBtn->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    loginBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
    mainSizer->Add(loginBtn, 0, wxALIGN_CENTER | wxBOTTOM, 50);

    panel->SetSizer(mainSizer);
    Centre();
}

void LoginFrame::OnLogin(wxCommandEvent &event)
{
    if (loginCallback)
    {
        std::string user = GetEmail().ToStdString();
        std::string pass = GetPassword().ToStdString();
        loginCallback(user.c_str(), pass.c_str());
    }
}