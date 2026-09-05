#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

static const WCHAR *operational_state(IF_OPER_STATUS state) {
    switch (state) {
        case IfOperStatusUp: return L"Up";
        case IfOperStatusDown: return L"Down";
        case IfOperStatusDormant: return L"Dormant";
        case IfOperStatusNotPresent: return L"Not present";
        case IfOperStatusLowerLayerDown: return L"Lower layer down";
        default: return L"Unknown";
    }
}

int wmain(void) {
    ULONG size = 15000;
    IP_ADAPTER_ADDRESSES *addresses = malloc(size);
    DWORD result;
    if (!addresses) { fwprintf(stderr, L"Out of memory.\n"); return 1; }
    result = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST |
             GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER, NULL, addresses, &size);
    if (result == ERROR_BUFFER_OVERFLOW) {
        free(addresses); addresses = malloc(size);
        if (!addresses) { fwprintf(stderr, L"Out of memory.\n"); return 1; }
        result = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST |
                 GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER, NULL, addresses, &size);
    }
    if (result != NO_ERROR) {
        fwprintf(stderr, L"GetAdaptersAddresses failed (%lu).\n", result);
        free(addresses); return 1;
    }
    wprintf(L"%-40ls %-18ls %ls\n", L"ADAPTER", L"STATUS", L"SPEED (Mbps)");
    for (IP_ADAPTER_ADDRESSES *item = addresses; item; item = item->Next) {
        wprintf(L"%-40ls %-18ls %llu\n", item->FriendlyName,
                operational_state(item->OperStatus), item->TransmitLinkSpeed / 1000000ULL);
    }
    free(addresses);
    return 0;
}
