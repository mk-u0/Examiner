#ifndef _LOGIN_H_
#define _LOGIN_H_
#include <wx/wx.h>

class LoginFrame : public wxFrame {
public:
   
    LoginFrame();

    void setCallback(void (*loginCallback)(const char*, const char*)) {}

    wxString GetEmail() const { return emailCtrl->GetValue().Trim(); }
    wxString GetPassword() const { return passCtrl->GetValue().Trim(); }
    
private:
    wxTextCtrl* emailCtrl;
    wxTextCtrl* passCtrl;
    wxButton* loginBtn;

    void (*loginCallback)(const char*, const char*) = nullptr;

    void OnLogin(wxCommandEvent& event);
};

#endif