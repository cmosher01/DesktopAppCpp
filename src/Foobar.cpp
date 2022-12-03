#include <wx/app.h>

int main(int argc, char *argv[]) {
    const int status = wxEntry(argc, argv);
    if (status < 0) {
        return 1;
    }

    return status;
}
