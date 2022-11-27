#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PreferencesDialog.h"
#include "FoobarApp.h"
#include <wx/xrc/xmlres.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <filesystem>
#include <iostream>
#include <ostream>

wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
    EVT_TREE_SEL_CHANGED(XRCID("treItems"), PreferencesDialog::OnTreeSelectionChanged)
    EVT_BUTTON(XRCID("btnDuplicate"), PreferencesDialog::OnDuplicate)
    EVT_BUTTON(XRCID("btnDelete"), PreferencesDialog::OnDelete)
wxEND_EVENT_TABLE()

static const wxSize& SIZ_DLG = wxSize(1024,768);

PreferencesDialog::PreferencesDialog(wxWindow* parent) : parent(parent) {
}

PreferencesDialog::~PreferencesDialog() {
}

#define CTRL(t,n) t* n = XRCCTRL(*this, #n, t)

class TreeItemData : public wxTreeItemData {
    std::filesystem::path *m_path;
    bool m_editable;
public:
    TreeItemData() : m_path(NULL), m_editable(false) {}
    TreeItemData(const std::filesystem::path& path, bool editable) {
        m_path = new std::filesystem::path(path);
        m_editable = editable;
    }
    virtual bool isFile() { return true; }
    bool isEditable() { return m_editable; }
    const std::filesystem::path path() { return *m_path; }
};

class EmptyTreeItem : public TreeItemData {
    virtual bool isFile() { return false; }
};

class TreeSink : public wxDirTraverser {
public:
    TreeSink(wxTreeCtrl *tree, wxTreeItemId parent, const std::filesystem::path& dir, bool editable) :
        m_tree(tree), m_parent(parent), m_dir(dir), m_editable(editable) {
    }

    wxDirTraverseResult OnFile(const wxString& filename) {
        wxFileName n = wxFileName::FileName(filename);
        if (n.GetExt() == "conf") {
            const std::filesystem::path& full = std::filesystem::path(n.GetFullName().t_str());
            const std::filesystem::path path = m_dir / full;
            m_tree->AppendItem(m_parent, n.GetName(), -1, -1, new TreeItemData(path, m_editable));
        }
        return wxDIR_CONTINUE;
    }

    wxDirTraverseResult OnDir(const wxString& dirname) {
        return wxDIR_CONTINUE;
    }
private:
    wxTreeCtrl *m_tree;
    wxTreeItemId m_parent;
    const std::filesystem::path& m_dir;
    bool m_editable;
};

static void fillDir(wxTreeCtrl *treItems, wxTreeItemId item, const std::filesystem::path& dir, bool editable = false) {
    TreeSink sink(treItems, item, dir, editable);
    wxDir dirBuiltIn = wxDir(dir.c_str());
    dirBuiltIn.Traverse(sink, wxEmptyString, wxDIR_FILES | wxDIR_HIDDEN);
}

void PreferencesDialog::BuildItemTree() {
    CTRL(wxTreeCtrl, treItems);

    treItems->DeleteAllItems();

    wxTreeItemId configs = treItems->AddRoot(wxT("configurations"), -1, -1, new EmptyTreeItem());
    wxTreeItemId built_in = treItems->AppendItem(configs, wxT("built-in"), -1, -1, new EmptyTreeItem());
    fillDir(treItems, built_in, wxGetApp().GetResDir());
    wxTreeItemId user = treItems->AppendItem(configs, wxT("user"), -1, -1, new EmptyTreeItem());
    fillDir(treItems, user, wxGetApp().GetConfigDir(), true);

    treItems->ExpandAll();
}

void PreferencesDialog::OnInit() {
    wxXmlResource::Get()->LoadDialog(this, this->parent, "Preferences");

    SetSize(SIZ_DLG);

    BuildItemTree();

    CTRL(wxTreeCtrl, treItems);
    treItems->SetFocus();
    treItems->SelectItem(treItems->GetRootItem());
}

void PreferencesDialog::OnTreeSelectionChanged(wxTreeEvent& evt) {
    // note: we don't get the first select upon dialog creation,
    // nor the final de-select upon dialog destruction

    CTRL(wxTreeCtrl, treItems);

    TreeItemData* dataOld = (TreeItemData*)treItems->GetItemData(evt.GetOldItem());
    wxString pathOld = "(not a file)";
    if (dataOld->isFile()) {
        pathOld = dataOld->path().c_str();
    }

    TreeItemData* dataNew = (TreeItemData*)treItems->GetItemData(evt.GetItem());
    wxString pathNew = "(not a file)";
    if (dataNew->isFile()) {
        pathNew = dataNew->path().c_str();
    }

    std::cout << "selection changed: " << pathOld << " to " << pathNew << std::endl;
}



void PreferencesDialog::OnDuplicate(wxCommandEvent& evt) {
    CTRL(wxTreeCtrl, treItems);
    TreeItemData* data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        std::cout << "DUPLICATE " << data->path().c_str() << std::endl;
    } else {
        std::cout << "(not a file)" << std::endl;
    }
}

void PreferencesDialog::OnDelete(wxCommandEvent& evt) {
    CTRL(wxTreeCtrl, treItems);
    TreeItemData* data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        if (data->isEditable()) {
            std::cout << "DELETE " << data->path().c_str() << std::endl;
        } else {
            std::cout << "Can't delete " << data->path().c_str() << std::endl;
        }
    } else {
        std::cout << "(not a file)" << std::endl;
    }
}
