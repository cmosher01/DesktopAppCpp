#include "FoobarApp.h"
#include "FoobarFrame.h"
#include <boost/log/trivial.hpp>

wxIMPLEMENT_APP_NO_MAIN(FoobarApp);

bool FoobarApp::OnInit()
{
    FoobarFrame *frame = new FoobarFrame();
    frame->Show(true);

    BOOST_LOG_TRIVIAL(info) << "An informational severity message";

    return true;
}
