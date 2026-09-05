#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls BACKUP_FILE RESTORE_PATH\n", argv[0]); return 2; }
    if (!CopyFileW(argv[1], argv[2], TRUE)) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_EXISTS) fwprintf(stderr, L"Restore path exists; nothing was overwritten.\n");
        else fwprintf(stderr, L"Restore failed (%lu).\n", error);
        return 1;
    }
    wprintf(L"Restored safely to: %ls\n", argv[2]); return 0;
}
