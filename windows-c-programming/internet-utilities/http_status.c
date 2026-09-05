#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib, "Wininet.lib")

int wmain(int argc, WCHAR **argv) {
    HINTERNET session, request; DWORD status, size = sizeof(status);
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls URL\n", argv[0]); return 2; }
    session = InternetOpenW(L"SimpleInternetUtility/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!session) return 1;
    request = InternetOpenUrlW(session, argv[1], NULL, 0, INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD, 0);
    if (!request) { fwprintf(stderr, L"Request failed (%lu).\n", GetLastError()); InternetCloseHandle(session); return 1; }
    if (!HttpQueryInfoW(request, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &status, &size, NULL)) {
        fwprintf(stderr, L"Unable to read status (%lu).\n", GetLastError()); status = 0;
    }
    wprintf(L"HTTP status: %lu\n", status);
    InternetCloseHandle(request); InternetCloseHandle(session); return status ? 0 : 1;
}
