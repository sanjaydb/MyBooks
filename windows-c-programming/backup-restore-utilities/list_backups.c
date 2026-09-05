#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    WCHAR pattern[32768]; WIN32_FIND_DATAW item; HANDLE search;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls BACKUP_DIRECTORY\n", argv[0]); return 2; }
    swprintf_s(pattern, ARRAYSIZE(pattern), L"%ls\\*", argv[1]); search = FindFirstFileW(pattern, &item);
    if (search == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"Unable to open backup directory (%lu).\n", GetLastError()); return 1; }
    do {
        if (wcscmp(item.cFileName, L".") && wcscmp(item.cFileName, L".."))
            wprintf(L"%-6ls %ls\n", (item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? L"[DIR]" : L"[FILE]", item.cFileName);
    } while (FindNextFileW(search, &item));
    FindClose(search); return 0;
}
