#include "FoobarApp.h"
#include "FoobarFrame.h"

wxIMPLEMENT_APP_NO_MAIN(FoobarApp);

bool FoobarApp::OnInit()
{
    FoobarFrame *frame = new FoobarFrame();
    frame->Show(true);

    return true;
}
