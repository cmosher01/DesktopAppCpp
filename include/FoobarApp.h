#ifndef FOOBAR_APP_H
#define FOOBAR_APP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class FoobarApp : public wxApp {
public:
    virtual bool OnInit();
};

#endif
