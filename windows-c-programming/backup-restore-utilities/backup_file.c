#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    SYSTEMTIME now; WCHAR output[32768]; const WCHAR *name;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls SOURCE_FILE BACKUP_DIRECTORY\n", argv[0]); return 2; }
    name = wcsrchr(argv[1], L'\\'); name = name ? name + 1 : argv[1]; GetLocalTime(&now);
    if (swprintf_s(output, ARRAYSIZE(output), L"%ls\\%04u%02u%02u_%02u%02u%02u_%ls", argv[2],
        now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, name) < 0) return 2;
    if (!CreateDirectoryW(argv[2], NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        fwprintf(stderr, L"Unable to create backup directory (%lu).\n", GetLastError()); return 1;
    }
    if (!CopyFileW(argv[1], output, TRUE)) { fwprintf(stderr, L"Backup failed (%lu).\n", GetLastError()); return 1; }
    wprintf(L"Backup created: %ls\n", output); return 0;
}
