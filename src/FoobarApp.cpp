#include "FoobarApp.h"
#include "FoobarFrame.h"

wxIMPLEMENT_APP(FoobarApp);

bool FoobarApp::OnInit()
{
    FoobarFrame *frame = new FoobarFrame();
    frame->Show(true);
    return true;
}
