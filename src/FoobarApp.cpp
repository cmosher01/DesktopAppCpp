#include "FoobarApp.h"
#if wxUSE_GUI
#include "FoobarFrame.h"
#endif
#include <wx/stdpaths.h>
#include <boost/log/trivial.hpp>

wxIMPLEMENT_APP_NO_MAIN(FoobarApp);

#define StdDir(n) BOOST_LOG_TRIVIAL(info) << "    " #n " dir: " << wxStandardPaths::Get().Get##n##Dir()
#define StdUserDir(n) BOOST_LOG_TRIVIAL(info) << "    User " #n " dir: " << wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_##n)

bool FoobarApp::OnInit()
{
    SetVendorName("nu.mine.mosher");

#ifdef __WXMSW__
    wxStandardPaths::Get().DontIgnoreAppSubDir()
#endif
    wxStandardPaths::Get().SetFileLayout(wxStandardPaths::FileLayout_XDG);
    wxStandardPaths::Get().UseAppInfo(wxStandardPaths::AppInfo_AppName | wxStandardPaths::AppInfo_VendorName);



    BOOST_LOG_TRIVIAL(info) << "App name: " << GetAppName();
    BOOST_LOG_TRIVIAL(info) << "App display name: " << GetAppDisplayName();
    BOOST_LOG_TRIVIAL(info) << "Vendor name: " << GetVendorName();
    BOOST_LOG_TRIVIAL(info) << "Vendor display name: " << GetVendorDisplayName();
    BOOST_LOG_TRIVIAL(info) << "Class name: " << GetClassName();



    BOOST_LOG_TRIVIAL(info) << "Install prefix: " << wxStandardPaths::Get().GetInstallPrefix();
    BOOST_LOG_TRIVIAL(info) << "Executable path: " << wxStandardPaths::Get().GetExecutablePath();
    BOOST_LOG_TRIVIAL(info) << "test config file name: " << wxStandardPaths::Get().MakeConfigFileName(wxString("test"));

    BOOST_LOG_TRIVIAL(info) << "Standard directories";
    StdDir(Plugins);
    StdDir(Resources);
    BOOST_LOG_TRIVIAL(info) << "    LocalizedResources (en) dir: " << wxStandardPaths::Get().GetLocalizedResourcesDir(wxString("en"), wxStandardPaths::ResourceCat_None);
    StdDir(Config);
    StdDir(UserConfig);

    StdUserDir(Cache);

    StdDir(Data);
    StdDir(LocalData);
    StdDir(UserData);
    StdDir(UserLocalData);

    StdDir(AppDocuments);
    //StdDir(Documents); same as StdUserDir(Documents)
    StdUserDir(Documents);
    StdUserDir(Desktop);
    StdUserDir(Downloads);
    StdUserDir(Music);
    StdUserDir(Pictures);
    StdUserDir(Videos);

    StdDir(Temp);




#if wxUSE_GUI
    FoobarFrame *frame = new FoobarFrame();
    frame->Show(true);
    return true;
#else
    return false;
#endif
}
