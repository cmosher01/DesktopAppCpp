#ifndef FOOBAR_FRAME_H
#define FOOBAR_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class FoobarFrame : public wxFrame {
public:
    FoobarFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif
