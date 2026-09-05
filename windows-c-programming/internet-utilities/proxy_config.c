#define UNICODE
#define _UNICODE
#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#pragma comment(lib, "Winhttp.lib")

int wmain(void) {
    WINHTTP_CURRENT_USER_IE_PROXY_CONFIG config = {0};
    if (!WinHttpGetIEProxyConfigForCurrentUser(&config)) {
        fwprintf(stderr, L"Unable to read proxy configuration (%lu).\n", GetLastError()); return 1;
    }
    wprintf(L"Automatically detect: %ls\n", config.fAutoDetect ? L"Yes" : L"No");
    wprintf(L"Configuration URL:    %ls\n", config.lpszAutoConfigUrl ? config.lpszAutoConfigUrl : L"(none)");
    wprintf(L"Proxy:                %ls\n", config.lpszProxy ? config.lpszProxy : L"(none)");
    wprintf(L"Proxy bypass:         %ls\n", config.lpszProxyBypass ? config.lpszProxyBypass : L"(none)");
    GlobalFree(config.lpszAutoConfigUrl); GlobalFree(config.lpszProxy); GlobalFree(config.lpszProxyBypass); return 0;
}
