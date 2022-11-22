#ifndef FOOBAR_FRAME_H
#define FOOBAR_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>

class FoobarFrame : public wxFrame {
public:
    FoobarFrame();

    void DoInit(std::string logfile);

private:
    void OnExit(wxCommandEvent& event);
    void OnPreferences(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void InitMenuBar();
    void InitStatusBar();

    std::string logfile;
};

#endif
