#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    WIN32_FILE_ATTRIBUTE_DATA info; ULARGE_INTEGER size;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls UNC_PATH\n", argv[0]); return 2; }
    if (!GetFileAttributesExW(argv[1], GetFileExInfoStandard, &info)) {
        fwprintf(stderr, L"Unable to query path (%lu).\n", GetLastError()); return 1;
    }
    size.HighPart = info.nFileSizeHigh; size.LowPart = info.nFileSizeLow;
    wprintf(L"Path:       %ls\nType:       %ls\n", argv[1],
            (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? L"Directory" : L"File");
    if (!(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) wprintf(L"Size:       %llu bytes\n", size.QuadPart);
    wprintf(L"Read-only:  %ls\n", (info.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? L"Yes" : L"No");
    return 0;
}
