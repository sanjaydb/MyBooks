#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    HANDLE pipe; DWORD bytesWritten, size;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls MESSAGE\n", argv[0]); return 2; }
    if (!WaitNamedPipeW(L"\\\\.\\pipe\\SimpleIpcPipe", 5000)) {
        fwprintf(stderr, L"Named pipe is unavailable (%lu).\n", GetLastError()); return 1;
    }
    pipe = CreateFileW(L"\\\\.\\pipe\\SimpleIpcPipe", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (pipe == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"CreateFile failed (%lu).\n", GetLastError()); return 1; }
    size = (DWORD)((wcslen(argv[1]) + 1) * sizeof(WCHAR));
    if (!WriteFile(pipe, argv[1], size, &bytesWritten, NULL)) {
        fwprintf(stderr, L"WriteFile failed (%lu).\n", GetLastError()); CloseHandle(pipe); return 1;
    }
    wprintf(L"Message sent.\n"); CloseHandle(pipe); return 0;
}
