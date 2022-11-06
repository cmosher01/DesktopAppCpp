#if wxUSE_GUI

#include "FoobarFrame.h"

enum {
    ID_Hello = 1
};

FoobarFrame::FoobarFrame() : wxFrame(nullptr, wxID_ANY, "Hello World") {
    wxMenu *menuFile = new wxMenu();
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &FoobarFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &FoobarFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &FoobarFrame::OnExit, this, wxID_EXIT);
}

void FoobarFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void FoobarFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox(
        "This is a wxWidgets Hello World example",
        "About Hello World",
        wxOK | wxICON_INFORMATION);
}

void FoobarFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}

#endif
