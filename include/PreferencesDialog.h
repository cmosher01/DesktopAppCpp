#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <wx/dialog.h>
#include <wx/treectrl.h>

class PreferencesDialog : public wxDialog {
    wxWindow *parent;

    void BuildItemTree();
    void OnTreeSelectionChanged(wxTreeEvent& evt);
    void OnDuplicate(wxCommandEvent& evt);
    void OnDelete(wxCommandEvent& evt);

    wxDECLARE_EVENT_TABLE();

    public:
    PreferencesDialog(wxWindow *parent);
    ~PreferencesDialog();

    void OnInit();
};

#endif /* PREFERENCESDIALOG_H */
