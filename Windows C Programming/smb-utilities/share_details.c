#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(int argc, WCHAR **argv) {
    SHARE_INFO_2 *info = NULL; NET_API_STATUS status;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls \\\\SERVER SHARE_NAME\n", argv[0]); return 2; }
    status = NetShareGetInfo(argv[1], argv[2], 2, (LPBYTE *)&info);
    if (status != NERR_Success) { fwprintf(stderr, L"NetShareGetInfo failed (%lu).\n", status); return 1; }
    wprintf(L"Name:        %ls\n", info->shi2_netname);
    wprintf(L"Local path:  %ls\n", info->shi2_path ? info->shi2_path : L"(not disclosed)");
    wprintf(L"Comment:     %ls\n", info->shi2_remark ? info->shi2_remark : L"");
    wprintf(L"Connections: %lu\n", info->shi2_current_uses);
    NetApiBufferFree(info); return 0;
}
