#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Wininet.lib")

int wmain(int argc, WCHAR **argv) {
    HINTERNET session, request; WCHAR *headers; DWORD size = 0;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls URL\n", argv[0]); return 2; }
    session = InternetOpenW(L"SimpleInternetUtility/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!session) return 1;
    request = InternetOpenUrlW(session, argv[1], NULL, 0, INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD, 0);
    if (!request) { InternetCloseHandle(session); return 1; }
    HttpQueryInfoW(request, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &size, NULL);
    headers = malloc(size);
    if (!headers || !HttpQueryInfoW(request, HTTP_QUERY_RAW_HEADERS_CRLF, headers, &size, NULL)) {
        fwprintf(stderr, L"Unable to read headers (%lu).\n", GetLastError()); free(headers); InternetCloseHandle(request); InternetCloseHandle(session); return 1;
    }
    wprintf(L"%ls", headers); free(headers); InternetCloseHandle(request); InternetCloseHandle(session); return 0;
}
