#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PreferencesDialog.h"
#include "FoobarApp.h"
#include <wx/msgdlg.h>
#include <wx/treectrl.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/textdlg.h>
#include <wx/xrc/xmlres.h>
#include <wx/config.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <boost/log/trivial.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#define CTRL(t,n) t* n = XRCCTRL(*this, #n, t)

static const wxSize& SIZ_DLG = wxSize(1024,768);



wxBEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)
    EVT_CLOSE(PreferencesDialog::OnClose)
    EVT_BUTTON(wxID_OK, PreferencesDialog::OnCloseButton)
    EVT_TREE_SEL_CHANGED(XRCID("treItems"), PreferencesDialog::OnTreeSelectionChanged)
    EVT_CHECKBOX(XRCID("chkActive"), PreferencesDialog::OnActive)
    EVT_BUTTON(XRCID("btnDuplicate"), PreferencesDialog::OnDuplicate)
    EVT_BUTTON(XRCID("btnDelete"), PreferencesDialog::OnDelete)
    EVT_BUTTON(XRCID("btnRename"), PreferencesDialog::OnRename)
wxEND_EVENT_TABLE()







class TreeItemData : public wxTreeItemData {
    const std::filesystem::path *m_path;
    const bool m_editable;
public:
    TreeItemData() : m_path(NULL), m_editable(false) {}
    TreeItemData(const std::filesystem::path& path, bool editable) :
        m_path(new std::filesystem::path(path)),
        m_editable(editable) {
    }
    virtual bool isFile() const { return true; }
    bool isEditable() const { return m_editable; }
    const std::filesystem::path path() const { return *m_path; }
};

class EmptyTreeItem : public TreeItemData {
    virtual bool isFile() const { return false; }
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
    const wxTreeItemId m_parent;
    const std::filesystem::path& m_dir;
    const bool m_editable;
};




PreferencesDialog::PreferencesDialog(wxWindow* parent) : parent(parent) {
}

PreferencesDialog::~PreferencesDialog() {
}

void PreferencesDialog::OnClose(wxCloseEvent& event) {
    CTRL(wxTreeCtrl, treItems);
    const TreeItemData *data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        if (data->isEditable()) {
            Save(data->path());
        }
    }
    EndModal(wxID_OK);
}

static void fillDir(wxTreeCtrl *treItems, wxTreeItemId item, const std::filesystem::path& dir, bool editable = false) {
    TreeSink sink(treItems, item, dir, editable);
    wxDir dirBuiltIn = wxDir(dir.c_str());
    dirBuiltIn.Traverse(sink, wxEmptyString, wxDIR_FILES | wxDIR_HIDDEN);
}

void PreferencesDialog::BuildItemTree() {
    CTRL(wxTreeCtrl, treItems);

    treItems->DeleteAllItems();

    wxTreeItemId configs = treItems->AddRoot(wxT("configurations"), -1, -1, new EmptyTreeItem());

    wxTreeItemId user = treItems->AppendItem(configs, wxT("user"), -1, -1, new EmptyTreeItem());
    fillDir(treItems, user, wxGetApp().GetConfigDir(), true);
    treItems->SortChildren(user);

    wxTreeItemId built_in = treItems->AppendItem(configs, wxT("built-in"), -1, -1, new EmptyTreeItem());
    fillDir(treItems, built_in, wxGetApp().GetResDir());
    treItems->SortChildren(built_in);

    treItems->ExpandAll();

    this->GetSizer()->Layout();
}

void PreferencesDialog::OnInit() {
    wxConfigBase *appconf = wxConfigBase::Get();
    if (!appconf->Read(wxT("/ActivePreferences/name"), &this->active)) {
        // TODO what to do when no config?
        this->active = ".template";
        appconf->Write(wxT("/ActivePreferences/name"), this->active);
        appconf->Flush();
    }

    wxXmlResource::Get()->LoadDialog(this, this->parent, "Preferences");

    SetSize(SIZ_DLG);

    BuildItemTree();

    CTRL(wxTreeCtrl, treItems);
    treItems->SetFocus();
    treItems->SelectItem(treItems->GetRootItem());
}

void PreferencesDialog::Save(const std::filesystem::path& to) {
    CTRL(wxTextCtrl, txtConfig);
    const wxString sConfig = txtConfig->GetValue();
    if (sConfig != this->sOrigConfig) {
        std::ofstream out(to);
        out << sConfig;
        this->sOrigConfig = sConfig;
    }
}

void PreferencesDialog::OnTreeSelectionChanged(wxTreeEvent& evt) {
    // note: we don't get the first select upon dialog creation,
    // nor the final de-select upon dialog destruction

    CTRL(wxTreeCtrl, treItems);
    CTRL(wxStaticText, txtName);
    CTRL(wxTextCtrl, txtConfig);
    CTRL(wxCheckBox, chkActive);

    const TreeItemData *dataOld = (TreeItemData*)treItems->GetItemData(evt.GetOldItem());
    wxString pathOld = "(not a file)";
    if (dataOld->isFile()) {
        pathOld = dataOld->path().c_str();
        Save(dataOld->path());
    }

    const TreeItemData *dataNew = (TreeItemData*)treItems->GetItemData(evt.GetItem());
    wxString pathNew = "(not a file)";
    if (dataNew->isFile()) {
        pathNew = dataNew->path().c_str();
        std::ifstream t(dataNew->path());
        std::stringstream buffer;
        buffer << t.rdbuf();
        this->sOrigConfig = buffer.str();
        txtConfig->SetValue(this->sOrigConfig);
        wxString name = wxFileName::FileName(dataNew->path().c_str()).GetName();
        txtName->SetLabel(name);
        chkActive->SetValue(name == this->active);
    } else {
        this->sOrigConfig = wxEmptyString;
        txtConfig->SetValue(this->sOrigConfig);
        txtName->SetLabel(wxEmptyString);
        chkActive->SetValue(false);
    }
}

void PreferencesDialog::PreSelectUserConfigItemName(const std::filesystem::path& n) {
    CTRL(wxTreeCtrl, treItems);
    wxTreeItemId id = treItems->GetRootItem();
    wxTreeItemIdValue ctx;
    wxTreeItemId i = treItems->GetFirstChild(id, ctx);
    while (i.IsOk() && treItems->GetItemText(i) != wxT("user")) {
        i = treItems->GetNextChild(id, ctx);
    }
    if (!i.IsOk()) {
        return;
    }

    id = i;
    i = treItems->GetFirstChild(id, ctx);
    while (i.IsOk() && treItems->GetItemText(i) != wxFileName::FileName(n.c_str()).GetName()) {
        i = treItems->GetNextChild(id, ctx);
    }
    if (!i.IsOk()) {
        return;
    }

    treItems->SelectItem(i);
    treItems->SetFocus();
}

const std::filesystem::path BuildNewConfFilePath() {
    std::filesystem::path f = wxGetApp().GetConfigDir();

    wxString ts = to_iso_string(boost::posix_time::microsec_clock::universal_time());
    ts.Replace(wxT("."), wxT("_"));
    f /= (wxT("Untitled_") + ts + wxT(".conf")).t_str();

    BOOST_LOG_TRIVIAL(info) << "will create file: " << f.c_str();

    return f;
}

void PreferencesDialog::OnActive(wxCommandEvent& evt) {
    if (evt.IsChecked()) {
        CTRL(wxTreeCtrl, treItems);
        const TreeItemData *data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
        if (data->isFile()) {
            const std::filesystem::path p = data->path();
            wxString name = wxFileName::FileName(p.c_str()).GetName();
            this->active = name;
            wxConfigBase::Get()->Write(wxT("/ActivePreferences/name"), this->active);
            BuildItemTree(); // invalidates "data" pointer variable
            PreSelectUserConfigItemName(p);
        }
    } else {
        // TODO what if they uncheck the active checkbox?
    }
}

void PreferencesDialog::OnDuplicate(wxCommandEvent& evt) {
    CTRL(wxTreeCtrl, treItems);
    const TreeItemData *data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        if (data->isEditable()) {
            Save(data->path());
        }
        const std::filesystem::path f = BuildNewConfFilePath();
        BOOST_LOG_TRIVIAL(info) << "copy from: " << data->path().c_str();
        if (!std::filesystem::exists(f)) {
            std::filesystem::copy_file(data->path(), f, std::filesystem::copy_options::skip_existing);
            BuildItemTree();
            PreSelectUserConfigItemName(f);
        } else {
            BOOST_LOG_TRIVIAL(error) << "file already exists: " << f.c_str();
        }
    }
}

void PreferencesDialog::OnDelete(wxCommandEvent& evt) {
    CTRL(wxTreeCtrl, treItems);
    CTRL(wxStaticText, txtName);
    CTRL(wxTextCtrl, txtConfig);
    const TreeItemData *data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        if (data->isEditable()) {
            if (wxMessageBox(
                    wxT("Are you sure to want to permanently DELETE this configuration file?"),
                    wxT("Delete"), wxYES_NO|wxCENTER, this) == wxYES) {
                std::filesystem::remove(data->path());
                BuildItemTree();
                treItems->SetFocus();
                treItems->SelectItem(treItems->GetRootItem());
                // clear out fields (TODO is there a better way?)
                this->sOrigConfig = wxEmptyString;
                txtConfig->SetValue(this->sOrigConfig);
                txtName->SetLabel(wxEmptyString);
            }
        }
    }
}

void PreferencesDialog::OnRename(wxCommandEvent& evt) {
    CTRL(wxTreeCtrl, treItems);
    const TreeItemData *data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        if (data->isEditable()) {
            Save(data->path());
            wxString name = wxFileName::FileName(data->path().c_str()).GetName();
            wxString newname = wxGetTextFromUser(wxT("new name:"), wxT("Rename configuration"), name, this, -1, -1, true);
            if (!newname.IsEmpty() && newname != name) {
                wxFileName fn(data->path().c_str());
                fn.SetName(newname);
                // TODO should we check for existence of name in built-in (to prevent override)?
                if (fn.Exists()) {
                    wxMessageBox(wxT("That name is already being used."), wxT("File exists"), wxOK|wxCENTER, this);
                } else {
                    const std::filesystem::path newpath(fn.GetFullPath().t_str());
                    std::filesystem::rename(data->path(), newpath);
                    BuildItemTree();
                    PreSelectUserConfigItemName(newpath);
                }
            }
        }
    }
}

void PreferencesDialog::OnCloseButton(wxCommandEvent& evt) {
    CTRL(wxTreeCtrl, treItems);
    const TreeItemData *data = (TreeItemData*)treItems->GetItemData(treItems->GetSelection());
    if (data->isFile()) {
        if (data->isEditable()) {
            Save(data->path());
        }
    }
    EndModal(wxID_OK);
}
