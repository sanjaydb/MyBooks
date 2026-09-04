#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    const WCHAR *directory = argc > 1 ? argv[1] : L".";
    WCHAR pattern[MAX_PATH];
    WIN32_FIND_DATAW item;
    HANDLE search;
    if (argc > 2) { fwprintf(stderr, L"Usage: %ls [directory]\n", argv[0]); return 2; }
    if (swprintf_s(pattern, ARRAYSIZE(pattern), L"%ls\\*", directory) < 0) {
        fwprintf(stderr, L"Directory path is too long.\n"); return 2;
    }
    search = FindFirstFileW(pattern, &item);
    if (search == INVALID_HANDLE_VALUE) {
        fwprintf(stderr, L"Unable to open directory (%lu).\n", GetLastError()); return 1;
    }
    do {
        if (wcscmp(item.cFileName, L".") == 0 || wcscmp(item.cFileName, L"..") == 0) continue;
        wprintf(L"%-6ls %ls\n", (item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? L"[DIR]" : L"[FILE]", item.cFileName);
    } while (FindNextFileW(search, &item));
    FindClose(search);
    return 0;
}
