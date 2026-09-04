#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    HANDLE mapping; WCHAR *view;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls MESSAGE\n", argv[0]); return 2; }
    mapping = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4096, L"Local\\SimpleIpcMemory");
    if (!mapping) { fwprintf(stderr, L"CreateFileMapping failed (%lu).\n", GetLastError()); return 1; }
    view = MapViewOfFile(mapping, FILE_MAP_WRITE, 0, 0, 4096);
    if (!view) { fwprintf(stderr, L"MapViewOfFile failed (%lu).\n", GetLastError()); CloseHandle(mapping); return 1; }
    wcsncpy_s(view, 4096 / sizeof(WCHAR), argv[1], _TRUNCATE);
    wprintf(L"Message published. Press Enter after running the reader.\n"); getwchar();
    UnmapViewOfFile(view); CloseHandle(mapping); return 0;
}
