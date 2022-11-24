#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PreferencesDialog.h"
#include "FoobarApp.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
wxEND_EVENT_TABLE()

PreferencesDialog::PreferencesDialog(wxWindow* parent) : parent(parent) {
}

PreferencesDialog::~PreferencesDialog() {
}

void PreferencesDialog::OnInit() {
    wxXmlResource::Get()->LoadDialog(this, this->parent, "Preferences");
}
