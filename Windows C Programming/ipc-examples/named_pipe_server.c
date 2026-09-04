#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    HANDLE pipe; WCHAR message[256]; DWORD bytesRead;
    pipe = CreateNamedPipeW(L"\\\\.\\pipe\\SimpleIpcPipe", PIPE_ACCESS_INBOUND,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, 0, sizeof(message), 0, NULL);
    if (pipe == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"CreateNamedPipe failed (%lu).\n", GetLastError()); return 1; }
    wprintf(L"Waiting for a client...\n");
    if (!ConnectNamedPipe(pipe, NULL) && GetLastError() != ERROR_PIPE_CONNECTED) {
        fwprintf(stderr, L"ConnectNamedPipe failed (%lu).\n", GetLastError()); CloseHandle(pipe); return 1;
    }
    if (!ReadFile(pipe, message, sizeof(message) - sizeof(WCHAR), &bytesRead, NULL)) {
        fwprintf(stderr, L"ReadFile failed (%lu).\n", GetLastError()); CloseHandle(pipe); return 1;
    }
    message[bytesRead / sizeof(WCHAR)] = L'\0'; wprintf(L"Received: %ls\n", message);
    DisconnectNamedPipe(pipe); CloseHandle(pipe); return 0;
}
