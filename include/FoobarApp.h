#ifndef FOOBAR_APP_H
#define FOOBAR_APP_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/string.h>
#include <filesystem>
#include <string>

class FoobarApp : public wxApp {
    const std::string id;
    const wxString version;
    std::filesystem::path logfile;
    std::filesystem::path resdir;
    std::filesystem::path conffile;
    std::filesystem::path confdir;
    std::filesystem::path docsdir;

    const std::filesystem::path BuildLogFilePath() const;
    void InitBoostLog();

public:
    FoobarApp();

    const std::string GetID() const;
    const wxString GetVersion() const;
    const std::filesystem::path GetLogFile() const;
    const std::filesystem::path GetResDir() const;
    const std::filesystem::path GetConfigFile() const;
    const std::filesystem::path GetConfigDir() const;
    const std::filesystem::path GetDocumentsDir() const;

    virtual bool OnInit() override;
    virtual int OnExit() override;
};

wxDECLARE_APP(FoobarApp);

#endif
