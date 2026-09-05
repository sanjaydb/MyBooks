#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR **argv) {
    WCHAR *server = argc == 2 ? argv[1] : NULL; FILE_INFO_3 *buffer = NULL;
    DWORD read, total; DWORD_PTR resume = 0; NET_API_STATUS status;
    if (argc > 2) { fwprintf(stderr, L"Usage: %ls [\\\\SERVER]\n", argv[0]); return 2; }
    wprintf(L"%-10ls %-20ls %ls\n", L"FILE ID", L"USER", L"PATH");
    do {
        status = NetFileEnum(server, NULL, NULL, 3, (LPBYTE *)&buffer, MAX_PREFERRED_LENGTH, &read, &total, &resume);
        if (status != NERR_Success && status != ERROR_MORE_DATA) { fwprintf(stderr, L"NetFileEnum failed (%lu). Administrator access may be required.\n", status); return 1; }
        for (DWORD i = 0; i < read; ++i)
            wprintf(L"%-10lu %-20ls %ls\n", buffer[i].fi3_id, buffer[i].fi3_username, buffer[i].fi3_pathname);
        if (buffer) { NetApiBufferFree(buffer); buffer = NULL; }
    } while (status == ERROR_MORE_DATA);
    return 0;
}
