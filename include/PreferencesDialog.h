#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <wx/dialog.h>

class PreferencesDialog : public wxDialog {
    wxWindow *parent;
    wxDECLARE_EVENT_TABLE();
public:
    PreferencesDialog(wxWindow *parent);
    ~PreferencesDialog();
    void OnInit();
};

#endif /* PREFERENCESDIALOG_H */
