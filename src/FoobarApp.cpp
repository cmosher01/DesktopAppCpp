#include "FoobarApp.h"
#include "FoobarFrame.h"
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/expressions.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>

wxIMPLEMENT_APP_NO_MAIN(FoobarApp);

bool FoobarApp::OnInit() {
    const std::string sidApp("nu.mine.mosher.foobar");
    const std::filesystem::path idApp(sidApp);
    const std::filesystem::path idApp_d(sidApp+".d");



    wxStandardPaths& stdpaths = wxStandardPaths::Get();
    stdpaths.SetFileLayout(wxStandardPaths::FileLayout_XDG);




    std::filesystem::path logfile = std::filesystem::path(stdpaths.GetUserDir(wxStandardPaths::Dir_Cache).t_str()) / idApp / "log";
    std::filesystem::create_directories(logfile);
    logfile = std::filesystem::canonical(logfile);

    const std::string ts = to_iso_string(boost::posix_time::second_clock::universal_time());
    logfile /= ts + ".log";
    std::cout << "log file: " << logfile << std::endl;

    boost::log::add_file_log(
            boost::log::keywords::file_name = logfile,
            boost::log::keywords::auto_flush = true,
            boost::log::keywords::format = (
                boost::log::expressions::stream <<
                    to_iso_extended_string(boost::posix_time::microsec_clock::universal_time()) << "Z " <<
                    boost::log::trivial::severity << " " <<
                    boost::log::expressions::message
            ));
    boost::log::add_common_attributes();




    const std::filesystem::path exe = std::filesystem::path(stdpaths.GetExecutablePath().t_str());
    BOOST_LOG_TRIVIAL(info) << "Executable path: " << exe;



    const std::filesystem::path conf_d = std::filesystem::path(stdpaths.GetUserConfigDir().t_str()) / idApp_d;
    std::filesystem::create_directories(conf_d);
    BOOST_LOG_TRIVIAL(info) << "Configuration directory path: " << conf_d;
    const std::filesystem::path conf = std::filesystem::path(stdpaths.GetUserConfigDir().t_str()) / idApp;
    BOOST_LOG_TRIVIAL(info) << "Configuration      file path: " << conf;



    wxConfigBase::Set(new wxFileConfig("", "", sidApp));

    wxString confValue;
    if (wxConfigBase::Get()->Read("confItem", &confValue)) {
        std::cout << "Found confItem" << std::endl;
    } else {
        std::cout << "Could not find confItem" << std::endl;
        confValue = "defaultValue";
        wxConfigBase::Get()->Write("confItem", confValue);
    }
    std::cout << "confValue: " << confValue << std::endl << std::flush;
    wxConfigBase::Get()->Flush();



    const std::filesystem::path docs = std::filesystem::path(stdpaths.GetAppDocumentsDir().t_str()) / idApp;
    BOOST_LOG_TRIVIAL(info) << "User documents path: " << docs;



    FoobarFrame *frame = new FoobarFrame();
    frame->DoInit((std::string&)logfile);
    frame->Show(true);



    return true;
}



int FoobarApp::OnExit() {
    return 0;
}
