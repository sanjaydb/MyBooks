#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "Advapi32.lib")
int wmain(int argc, WCHAR **argv) {
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls FILE\n", argv[0]); return 2; }
    if (!DecryptFileW(argv[1], 0)) { fwprintf(stderr, L"DecryptFile failed (%lu).\n", GetLastError()); return 1; }
    wprintf(L"EFS encryption removed from: %ls\n", argv[1]); return 0;
}
