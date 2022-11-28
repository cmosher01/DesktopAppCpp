#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <wx/event.h>
#include <wx/dialog.h>
#include <wx/treectrl.h>
#include <filesystem>

class PreferencesDialog : public wxDialog {
    wxWindow *parent;
    wxString sOrigConfig;

    void BuildItemTree();
    void PreSelectUserConfigItemName(const std::filesystem::path& n);
    void Save(const std::filesystem::path& to);

    void OnClose(wxCloseEvent& event);
    void OnCloseButton(wxCommandEvent& evt);
    void OnTreeSelectionChanged(wxTreeEvent& evt);
    void OnDuplicate(wxCommandEvent& evt);
    void OnDelete(wxCommandEvent& evt);
    void OnRename(wxCommandEvent& evt);

    wxDECLARE_EVENT_TABLE();

public:
    PreferencesDialog(wxWindow *parent);
    ~PreferencesDialog();

    void OnInit();
};

#endif /* PREFERENCESDIALOG_H */
