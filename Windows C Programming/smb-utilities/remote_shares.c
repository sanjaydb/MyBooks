#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR **argv) {
    SHARE_INFO_1 *buffer = NULL; DWORD read, total, resume = 0; NET_API_STATUS status;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls \\\\SERVER\n", argv[0]); return 2; }
    wprintf(L"%-24ls %ls\n", L"SHARE", L"COMMENT");
    do {
        status = NetShareEnum(argv[1], 1, (LPBYTE *)&buffer, MAX_PREFERRED_LENGTH, &read, &total, &resume);
        if (status != NERR_Success && status != ERROR_MORE_DATA) { fwprintf(stderr, L"NetShareEnum failed (%lu).\n", status); return 1; }
        for (DWORD i = 0; i < read; ++i)
            wprintf(L"%-24ls %ls\n", buffer[i].shi1_netname, buffer[i].shi1_remark ? buffer[i].shi1_remark : L"");
        if (buffer) { NetApiBufferFree(buffer); buffer = NULL; }
    } while (status == ERROR_MORE_DATA);
    return 0;
}
