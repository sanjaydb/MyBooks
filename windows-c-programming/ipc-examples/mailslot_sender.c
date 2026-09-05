#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    HANDLE slot; DWORD bytesWritten, size;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls MESSAGE\n", argv[0]); return 2; }
    slot = CreateFileW(L"\\\\.\\mailslot\\SimpleIpcSlot", GENERIC_WRITE, FILE_SHARE_READ,
                       NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (slot == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"Start mailslot_receiver first (%lu).\n", GetLastError()); return 1; }
    size = (DWORD)((wcslen(argv[1]) + 1) * sizeof(WCHAR));
    if (!WriteFile(slot, argv[1], size, &bytesWritten, NULL)) {
        fwprintf(stderr, L"WriteFile failed (%lu).\n", GetLastError()); CloseHandle(slot); return 1;
    }
    wprintf(L"Message sent.\n"); CloseHandle(slot); return 0;
}
