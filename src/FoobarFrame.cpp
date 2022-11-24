#include "FoobarFrame.h"
#include "FoobarApp.h"
#include "PreferencesDialog.h"
#include <wx/persist/toplevel.h>



FoobarFrame::FoobarFrame() : wxFrame(nullptr, wxID_ANY, "Foobar") {
}



void FoobarFrame::DoInit() {
    InitMenuBar();
    InitStatusBar();

    if (!wxPersistentRegisterAndRestore(this, "main")) {
        Center();
    }
}

void FoobarFrame::InitMenuBar() {
    wxMenuBar *menuBar = new wxMenuBar();
    SetMenuBar(menuBar);

    wxMenu *menuFile = new wxMenu();
    menuBar->Append(menuFile, "&File");
    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, &FoobarFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &FoobarFrame::OnPreferences, this, wxID_PREFERENCES);

    wxMenu *menuEdit = new wxMenu();
    menuBar->Append(menuEdit, "&Edit");
    menuEdit->Append(wxID_PREFERENCES);

    wxMenu *menuHelp = new wxMenu();
    menuBar->Append(menuHelp, "&Help");
    menuHelp->Append(wxID_ABOUT);
    Bind(wxEVT_MENU, &FoobarFrame::OnAbout, this, wxID_ABOUT);
}

void FoobarFrame::InitStatusBar() {
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}



void FoobarFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void FoobarFrame::OnAbout(wxCommandEvent& event) {
    std::string msg;
    msg = "Current log file:\n";
    msg += wxGetApp().GetLogFile().c_str();
    wxMessageBox(msg, "About Hello World", wxOK | wxICON_INFORMATION);
}

void FoobarFrame::OnPreferences(wxCommandEvent& event) {
    PreferencesDialog *dlg = new PreferencesDialog(this);
    dlg->OnInit();
    dlg->ShowModal();
}
