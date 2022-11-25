#include "config.h"
#include "FoobarApp.h"
#include "FoobarFrame.h"
#include <wx/xrc/xmlres.h>
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
#include <iostream>
#include <algorithm>





static std::filesystem::path dirCache() {
    return std::filesystem::path(wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Cache).t_str());
}

static std::filesystem::path dirConfig() {
    return std::filesystem::path(wxStandardPaths::Get().GetUserConfigDir().t_str());
}

static std::filesystem::path dirDocuments() {
    return std::filesystem::path(wxStandardPaths::Get().GetAppDocumentsDir().t_str());
}

static std::filesystem::path dirResources() {
    return std::filesystem::path(wxStandardPaths::Get().GetResourcesDir().t_str());
}





wxIMPLEMENT_APP_NO_MAIN(FoobarApp);

#ifndef PROJECT_VERSION
#define PROJECT_VERSION 0.0.1
#endif

FoobarApp::FoobarApp() : id("nu.mine.mosher.foobar"), version(wxSTRINGIZE_T(PROJECT_VERSION)) {
}

bool FoobarApp::OnInit() {
    if (!wxApp::OnInit()) {
        return false;
    }



    wxStandardPaths& stdpaths = wxStandardPaths::Get();
    //stdpaths.SetInstallPrefix(".");
    stdpaths.SetFileLayout(wxStandardPaths::FileLayout_XDG);



    InitBoostLog();




    this->confdir = dirConfig() / std::filesystem::path(GetID()+".d");
    std::filesystem::create_directories(this->confdir);
    BOOST_LOG_TRIVIAL(info) << "Configuration directory path: " << this->confdir;

    this->conffile = dirConfig() / std::filesystem::path(GetID());
    BOOST_LOG_TRIVIAL(info) << "Configuration      file path: " << this->conffile;
    wxConfigBase::Set(new wxFileConfig("", "", GetID()));

    this->docsdir = dirDocuments() / std::filesystem::path(GetID());
    BOOST_LOG_TRIVIAL(info) << "User document directory path: " << this->docsdir;

    const std::filesystem::path exe = std::filesystem::path(stdpaths.GetExecutablePath().t_str());
    std::cout << "Executable         file path: " << exe << std::endl;
    std::filesystem::path res = exe.parent_path();
    if (res.filename() == "bin" || res.filename() == "MacOS") {
        res = res.parent_path();
    }
    if (std::filesystem::is_directory(res / "share")) {
        res /= "share";
    }
    if (std::filesystem::is_directory(res / "Resources")) {
        res /= "Resources";
    }
    this->resdir = res;
    std::cout << "Resource      directory path: " << this->resdir << std::endl;

    wxXmlResource::Get()->InitAllHandlers();
    if (!wxXmlResource::Get()->LoadAllFiles(this->resdir.c_str())) {
        return false;
    }



    FoobarFrame *frame = new FoobarFrame();
    frame->DoInit();
    frame->Show();



    return true;
}

int FoobarApp::OnExit() {
    return 0;
}



const std::filesystem::path FoobarApp::GetLogFile() const {
    return this->logfile;
}

const std::filesystem::path FoobarApp::GetResDir() const {
    return this->resdir;
}

const std::string FoobarApp::GetID() const {
    return this->id;
}

const wxString FoobarApp::GetVersion() const {
    return this->version;
}

const std::filesystem::path FoobarApp::GetConfigFile() const {
    return this->conffile;
}

const std::filesystem::path FoobarApp::GetConfigDir() const
{
    return this->confdir;
}

const std::filesystem::path FoobarApp::GetDocumentsDir() const {
    return this->docsdir;
}



const std::filesystem::path FoobarApp::BuildLogFilePath() const {
    std::filesystem::path logfile =
        dirCache() /
        std::filesystem::path(GetID()) /
        std::filesystem::path("log");

    std::filesystem::create_directories(logfile);
    logfile = std::filesystem::canonical(logfile);

    const std::string ts = to_iso_string(boost::posix_time::second_clock::universal_time());
    logfile /= ts + ".log";

    return logfile;
}

void FoobarApp::InitBoostLog() {
    this->logfile = BuildLogFilePath();

    std::cout << "log file: " << this->logfile << std::endl;



    boost::log::add_file_log(
            boost::log::keywords::file_name = this->logfile,
            boost::log::keywords::auto_flush = true,
            boost::log::keywords::format = (
                boost::log::expressions::stream <<
                    to_iso_extended_string(boost::posix_time::microsec_clock::universal_time()) << "Z " <<
                    boost::log::trivial::severity << " " <<
                    boost::log::expressions::message
            ));

    boost::log::add_common_attributes();
}
