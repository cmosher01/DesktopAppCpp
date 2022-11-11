#include "FoobarApp.h"
#include "FoobarFrame.h"
#include <wx/stdpaths.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>

wxIMPLEMENT_APP_NO_MAIN(FoobarApp);

#define StdDir(n) BOOST_LOG_TRIVIAL(info) << "    " #n " dir: " << wxStandardPaths::Get().Get##n##Dir()
#define StdUserDir(n) BOOST_LOG_TRIVIAL(info) << "    User " #n " dir: " << wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_##n)

bool FoobarApp::OnInit()
{
    SetVendorName("nu.mine.mosher");

    // wxStandardPaths::Get().SetInstallPrefix("/opt");
    // wxStandardPaths::Get().SetInstallPrefix("/opt/foobar");
    // wxStandardPaths::Get().SetInstallPrefix("/opt/nu.mine.mosher");
    wxStandardPaths::Get().SetInstallPrefix("/opt/nu.mine.mosher/foobar");

#ifdef __WXMSW__
    wxStandardPaths::Get().DontIgnoreAppSubDir();
#endif
    // wxStandardPaths::Get().SetFileLayout(wxStandardPaths::FileLayout_XDG);
    wxStandardPaths::Get().UseAppInfo(wxStandardPaths::AppInfo_AppName | wxStandardPaths::AppInfo_VendorName);


    const wxString dirLog = wxStandardPaths::Get().GetUserLocalDataDir();
    std::string ts = to_iso_string(boost::posix_time::second_clock::universal_time());
    std::filesystem::path logfile;
    logfile += dirLog.ToStdString();
    std::filesystem::create_directories(logfile);
    logfile /= ts + ".log";
    std::cout << logfile << std::endl;
    boost::log::add_file_log(boost::log::keywords::file_name = logfile, boost::log::keywords::auto_flush = true);
    boost::log::add_common_attributes();

    BOOST_LOG_TRIVIAL(info) << "App name: " << GetAppName();
    BOOST_LOG_TRIVIAL(info) << "App display name: " << GetAppDisplayName();
    BOOST_LOG_TRIVIAL(info) << "Vendor name: " << GetVendorName();
    BOOST_LOG_TRIVIAL(info) << "Vendor display name: " << GetVendorDisplayName();
    BOOST_LOG_TRIVIAL(info) << "Class name: " << GetClassName();


#ifdef __WXGTK__
    BOOST_LOG_TRIVIAL(info) << "Install prefix: " << wxStandardPaths::Get().GetInstallPrefix();
#endif
    BOOST_LOG_TRIVIAL(info) << "Executable path: " << wxStandardPaths::Get().GetExecutablePath();
    // BOOST_LOG_TRIVIAL(info) << "test config file name: " << wxStandardPaths::Get().MakeConfigFileName(wxString("test"));

    BOOST_LOG_TRIVIAL(info) << "Standard directories";
    StdDir(Plugins);
    StdDir(Resources);
    BOOST_LOG_TRIVIAL(info) << "    LocalizedResources (en) dir: " << wxStandardPaths::Get().GetLocalizedResourcesDir(wxString("en"), wxStandardPaths::ResourceCat_None);
    StdDir(Config);
    StdDir(UserConfig);

    // StdUserDir(Cache);

    StdDir(Data);
    StdDir(LocalData);
    StdDir(UserData);
    StdDir(UserLocalData);

    StdDir(AppDocuments);
    //StdDir(Documents); same as StdUserDir(Documents)
    // StdUserDir(Documents);
    // StdUserDir(Desktop);
    // StdUserDir(Downloads);
    // StdUserDir(Music);
    // StdUserDir(Pictures);
    // StdUserDir(Videos);

    StdDir(Temp);



    FoobarFrame *frame = new FoobarFrame();
    frame->Show(true);
    return true;
}
