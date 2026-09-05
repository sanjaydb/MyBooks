#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    HANDLE mapping = OpenFileMappingW(FILE_MAP_READ, FALSE, L"Local\\SimpleIpcMemory");
    const WCHAR *view;
    if (!mapping) { fwprintf(stderr, L"Start shared_memory_writer first (%lu).\n", GetLastError()); return 1; }
    view = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0);
    if (!view) { fwprintf(stderr, L"MapViewOfFile failed (%lu).\n", GetLastError()); CloseHandle(mapping); return 1; }
    wprintf(L"Shared message: %ls\n", view);
    UnmapViewOfFile(view); CloseHandle(mapping); return 0;
}
