#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib, "Wininet.lib")

int wmain(void) {
    DWORD flags = 0;
    if (!InternetGetConnectedState(&flags, 0)) { wprintf(L"Windows reports no Internet connection.\n"); return 1; }
    wprintf(L"Windows reports an Internet connection.\nConnection types:");
    if (flags & INTERNET_CONNECTION_LAN) wprintf(L" LAN");
    if (flags & INTERNET_CONNECTION_MODEM) wprintf(L" Modem");
    if (flags & INTERNET_CONNECTION_PROXY) wprintf(L" Proxy");
    wprintf(L"\n"); return 0;
}
