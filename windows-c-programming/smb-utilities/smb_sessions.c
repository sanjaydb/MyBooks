#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR **argv) {
    WCHAR *server = argc == 2 ? argv[1] : NULL; SESSION_INFO_10 *buffer = NULL;
    DWORD read, total, resume = 0; NET_API_STATUS status;
    if (argc > 2) { fwprintf(stderr, L"Usage: %ls [\\\\SERVER]\n", argv[0]); return 2; }
    wprintf(L"%-24ls %-24ls %ls\n", L"CLIENT", L"USER", L"SECONDS");
    do {
        status = NetSessionEnum(server, NULL, NULL, 10, (LPBYTE *)&buffer, MAX_PREFERRED_LENGTH, &read, &total, &resume);
        if (status != NERR_Success && status != ERROR_MORE_DATA) { fwprintf(stderr, L"NetSessionEnum failed (%lu). Administrator access may be required.\n", status); return 1; }
        for (DWORD i = 0; i < read; ++i)
            wprintf(L"%-24ls %-24ls %lu\n", buffer[i].sesi10_cname, buffer[i].sesi10_username, buffer[i].sesi10_time);
        if (buffer) { NetApiBufferFree(buffer); buffer = NULL; }
    } while (status == ERROR_MORE_DATA);
    return 0;
}
