#define UNICODE
#define _UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#pragma comment(lib, "Netapi32.lib")

int wmain(void) {
    LPLOCALGROUP_INFO_1 buffer = NULL;
    DWORD read, total;
    DWORD_PTR resume = 0;
    NET_API_STATUS result;
    wprintf(L"%-32ls %ls\n", L"LOCAL GROUP", L"COMMENT");
    do {
        result = NetLocalGroupEnum(NULL, 1, (LPBYTE *)&buffer, MAX_PREFERRED_LENGTH,
                                   &read, &total, &resume);
        if (result != NERR_Success && result != ERROR_MORE_DATA) {
            fwprintf(stderr, L"NetLocalGroupEnum failed (%lu).\n", result);
            return 1;
        }
        for (DWORD i = 0; i < read; ++i) {
            wprintf(L"%-32ls %ls\n", buffer[i].lgrpi1_name,
                    buffer[i].lgrpi1_comment ? buffer[i].lgrpi1_comment : L"");
        }
        if (buffer) { NetApiBufferFree(buffer); buffer = NULL; }
    } while (result == ERROR_MORE_DATA);
    return 0;
}
