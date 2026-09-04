#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(void) {
    LPUSER_INFO_1 buffer = NULL;
    DWORD read, total, resume = 0;
    NET_API_STATUS result;
    wprintf(L"%-24ls %-10ls %ls\n", L"USER", L"STATUS", L"COMMENT");
    do {
        result = NetUserEnum(NULL, 1, FILTER_NORMAL_ACCOUNT, (LPBYTE *)&buffer,
                             MAX_PREFERRED_LENGTH, &read, &total, &resume);
        if (result != NERR_Success && result != ERROR_MORE_DATA) {
            fwprintf(stderr, L"NetUserEnum failed (%lu).\n", result);
            return 1;
        }
        for (DWORD i = 0; i < read; ++i) {
            const WCHAR *state = (buffer[i].usri1_flags & UF_ACCOUNTDISABLE) ? L"Disabled" : L"Enabled";
            wprintf(L"%-24ls %-10ls %ls\n", buffer[i].usri1_name, state,
                    buffer[i].usri1_comment ? buffer[i].usri1_comment : L"");
        }
        if (buffer) { NetApiBufferFree(buffer); buffer = NULL; }
    } while (result == ERROR_MORE_DATA);
    return 0;
}
