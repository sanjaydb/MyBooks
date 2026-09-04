#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    if (argc != 3) {
        fwprintf(stderr, L"Usage: %ls SOURCE_FILE DESTINATION_FILE\n", argv[0]);
        return 2;
    }
    if (!CopyFileW(argv[1], argv[2], TRUE)) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_EXISTS)
            fwprintf(stderr, L"Destination already exists; nothing was overwritten.\n");
        else
            fwprintf(stderr, L"CopyFile failed (%lu).\n", error);
        return 1;
    }
    wprintf(L"Copied successfully:\n  From: %ls\n  To:   %ls\n", argv[1], argv[2]);
    return 0;
}
