#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR **argv) {
    SERVER_INFO_101 *info = NULL; NET_API_STATUS status;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls \\\\SERVER\n", argv[0]); return 2; }
    status = NetServerGetInfo(argv[1], 101, (LPBYTE *)&info);
    if (status != NERR_Success) { fwprintf(stderr, L"NetServerGetInfo failed (%lu).\n", status); return 1; }
    wprintf(L"Server:  %ls\nVersion: %lu.%lu\nComment: %ls\n", info->sv101_name,
            info->sv101_version_major, info->sv101_version_minor,
            info->sv101_comment ? info->sv101_comment : L"");
    NetApiBufferFree(info); return 0;
}
