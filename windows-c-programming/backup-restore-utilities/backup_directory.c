#define UNICODE
#define _UNICODE
#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <wchar.h>
#pragma comment(lib, "Shell32.lib")

int wmain(int argc, WCHAR **argv) {
    SHFILEOPSTRUCTW operation = {0}; WCHAR source[32768], destination[32768];
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls SOURCE_DIRECTORY NEW_BACKUP_DIRECTORY\n", argv[0]); return 2; }
    if (GetFileAttributesW(argv[2]) != INVALID_FILE_ATTRIBUTES) { fwprintf(stderr, L"Destination already exists.\n"); return 1; }
    wcscpy_s(source, ARRAYSIZE(source), argv[1]); wcscpy_s(destination, ARRAYSIZE(destination), argv[2]);
    source[wcslen(source) + 1] = L'\0'; destination[wcslen(destination) + 1] = L'\0';
    operation.wFunc = FO_COPY; operation.pFrom = source; operation.pTo = destination;
    operation.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI | FOF_SILENT;
    if (SHFileOperationW(&operation) != 0 || operation.fAnyOperationsAborted) { fwprintf(stderr, L"Directory backup failed.\n"); return 1; }
    wprintf(L"Directory backup created: %ls\n", argv[2]); return 0;
}
