#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    HANDLE file; char buffer[4096]; DWORD bytesRead;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls \\\\SERVER\\SHARE\\file.txt\n", argv[0]); return 2; }
    file = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"Unable to open file (%lu).\n", GetLastError()); return 1; }
    for (;;) {
        if (!ReadFile(file, buffer, sizeof(buffer), &bytesRead, NULL)) {
            fwprintf(stderr, L"\nA read error occurred (%lu).\n", GetLastError()); CloseHandle(file); return 1;
        }
        if (bytesRead == 0) break;
        fwrite(buffer, 1, bytesRead, stdout);
    }
    CloseHandle(file); return 0;
}
