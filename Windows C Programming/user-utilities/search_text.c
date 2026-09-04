#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    FILE *file;
    WCHAR line[4096];
    unsigned long lineNumber = 0, matches = 0;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls FILE SEARCH_TEXT\n", argv[0]); return 2; }
    if (_wfopen_s(&file, argv[1], L"r, ccs=UTF-8") != 0) {
        fwprintf(stderr, L"Unable to open file: %ls\n", argv[1]); return 1;
    }
    while (fgetws(line, ARRAYSIZE(line), file)) {
        ++lineNumber;
        if (wcsstr(line, argv[2])) { wprintf(L"%lu: %ls", lineNumber, line); ++matches; }
    }
    fclose(file);
    wprintf(L"\nMatches: %lu\n", matches);
    return matches ? 0 : 1;
}
