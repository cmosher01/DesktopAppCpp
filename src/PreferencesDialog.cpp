#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PreferencesDialog.h"
#include "FoobarApp.h"
#include <wx/xrc/xmlres.h>
#include <wx/treectrl.h>
#include <wx/dir.h>
#include <wx/filename.h>

wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
wxEND_EVENT_TABLE()

static const wxSize& SIZ_DLG = wxSize(1024,768);

PreferencesDialog::PreferencesDialog(wxWindow* parent) : parent(parent) {
}

PreferencesDialog::~PreferencesDialog() {
}

#define CTRL(t,n) t* n = XRCCTRL(*this, #n, t)

class TreeSink : public wxDirTraverser {
public:
    TreeSink(wxTreeCtrl *tree, wxTreeItemId parent) : m_tree(tree), m_parent(parent) { }

    wxDirTraverseResult OnFile(const wxString& filename)
    {
        wxFileName n = wxFileName::FileName(filename);
        if (n.GetExt() == "conf") {
            m_tree->AppendItem(m_parent, n.GetName());
        }
        return wxDIR_CONTINUE;
    }

    wxDirTraverseResult OnDir(const wxString& dirname) {
        return wxDIR_CONTINUE;
    }
private:
    wxTreeCtrl *m_tree;
    wxTreeItemId m_parent;
};

void PreferencesDialog::OnInit() {
    wxXmlResource::Get()->LoadDialog(this, this->parent, "Preferences");

    this->SetSize(SIZ_DLG);

    CTRL(wxTreeCtrl, treItems);

    wxTreeItemId configs = treItems->AddRoot(wxT("configurations"));
    wxTreeItemId built_in = treItems->AppendItem(configs, wxT("built-in"));
    wxTreeItemId user = treItems->AppendItem(configs, wxT("user"));
    treItems->Expand(configs);

    TreeSink sinkBuiltIn(treItems, built_in);
    wxDir dirBuiltIn = (wxDir)wxGetApp().GetResDir().c_str();
    dirBuiltIn.Traverse(sinkBuiltIn, wxEmptyString, wxDIR_FILES | wxDIR_HIDDEN);
    treItems->Expand(built_in);

    // TODO user conf dir
    treItems->Expand(user);
}
