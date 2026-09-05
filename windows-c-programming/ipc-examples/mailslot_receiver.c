#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    HANDLE slot; WCHAR message[256]; DWORD bytesRead;
    slot = CreateMailslotW(L"\\\\.\\mailslot\\SimpleIpcSlot", 0, MAILSLOT_WAIT_FOREVER, NULL);
    if (slot == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"CreateMailslot failed (%lu).\n", GetLastError()); return 1; }
    wprintf(L"Waiting for a message...\n");
    if (!ReadFile(slot, message, sizeof(message) - sizeof(WCHAR), &bytesRead, NULL)) {
        fwprintf(stderr, L"ReadFile failed (%lu).\n", GetLastError()); CloseHandle(slot); return 1;
    }
    message[bytesRead / sizeof(WCHAR)] = L'\0'; wprintf(L"Received: %ls\n", message);
    CloseHandle(slot); return 0;
}
