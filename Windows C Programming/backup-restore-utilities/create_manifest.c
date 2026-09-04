#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    WCHAR pattern[32768]; WIN32_FIND_DATAW item; HANDLE search; FILE *output;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls DIRECTORY MANIFEST_FILE\n", argv[0]); return 2; }
    if (_wfopen_s(&output, argv[2], L"w, ccs=UTF-8") != 0) { fwprintf(stderr, L"Unable to create manifest.\n"); return 1; }
    swprintf_s(pattern, ARRAYSIZE(pattern), L"%ls\\*", argv[1]); search = FindFirstFileW(pattern, &item);
    if (search == INVALID_HANDLE_VALUE) { fclose(output); return 1; }
    fwprintf(output, L"TYPE\tSIZE_BYTES\tNAME\n");
    do {
        ULARGE_INTEGER size; size.HighPart = item.nFileSizeHigh; size.LowPart = item.nFileSizeLow;
        if (wcscmp(item.cFileName, L".") && wcscmp(item.cFileName, L".."))
            fwprintf(output, L"%ls\t%llu\t%ls\n", (item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? L"DIR" : L"FILE", size.QuadPart, item.cFileName);
    } while (FindNextFileW(search, &item));
    FindClose(search); fclose(output); wprintf(L"Manifest created: %ls\n", argv[2]); return 0;
}
