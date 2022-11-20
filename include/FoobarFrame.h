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

    void SetLogFile(std::string logfile);
    
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    std::string logfile;
};

#endif
