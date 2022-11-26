#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PreferencesDialog.h"
#include "FoobarApp.h"
#include <wx/xrc/xmlres.h>
#include <wx/treectrl.h>

wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
wxEND_EVENT_TABLE()

static const wxSize& SIZ_DLG = wxSize(1024,768);

PreferencesDialog::PreferencesDialog(wxWindow* parent) : parent(parent) {
}

PreferencesDialog::~PreferencesDialog() {
}

#define CTRL(t,n) t* n = XRCCTRL(*this, #n, t)

void PreferencesDialog::OnInit() {
    wxXmlResource::Get()->LoadDialog(this, this->parent, "Preferences");

    this->SetSize(SIZ_DLG);

    CTRL(wxTreeCtrl, treItems);
    wxTreeItemId configs = treItems->AddRoot("configurations");
    wxTreeItemId built_in = treItems->AppendItem(configs, "built-in");
    wxTreeItemId user = treItems->AppendItem(configs, "user");
    treItems->Expand(configs);
}
