#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls UNC_SOURCE LOCAL_DESTINATION\n", argv[0]); return 2; }
    if (!CopyFileW(argv[1], argv[2], TRUE)) {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_EXISTS) fwprintf(stderr, L"Destination exists; no file was overwritten.\n");
        else fwprintf(stderr, L"CopyFile failed (%lu).\n", error);
        return 1;
    }
    wprintf(L"Copied %ls to %ls\n", argv[1], argv[2]); return 0;
}
