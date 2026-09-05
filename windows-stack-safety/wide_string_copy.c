#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    WCHAR destination[32];
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls TEXT\n", argv[0]); return 2; }
    if (wcslen(argv[1]) >= ARRAYSIZE(destination)) {
        fwprintf(stderr, L"Text is too long; maximum is %zu characters.\n", ARRAYSIZE(destination) - 1);
        return 1;
    }
    if (wcscpy_s(destination, ARRAYSIZE(destination), argv[1]) != 0) return 1;
    wprintf(L"Copied safely: %ls\n", destination);
    return 0;
}
