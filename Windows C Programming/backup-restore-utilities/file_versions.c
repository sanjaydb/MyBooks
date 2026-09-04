#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    WCHAR pattern[32768]; WIN32_FIND_DATAW item; HANDLE search;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls BACKUP_DIRECTORY ORIGINAL_FILE_NAME\n", argv[0]); return 2; }
    if (swprintf_s(pattern, ARRAYSIZE(pattern), L"%ls\\*_%ls", argv[1], argv[2]) < 0) return 2;
    search = FindFirstFileW(pattern, &item);
    if (search == INVALID_HANDLE_VALUE) { wprintf(L"No backup versions found.\n"); return 1; }
    do { if (!(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) wprintf(L"%ls\n", item.cFileName); }
    while (FindNextFileW(search, &item));
    FindClose(search); return 0;
}
