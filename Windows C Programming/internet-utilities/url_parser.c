#define UNICODE
#define _UNICODE
#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#pragma comment(lib, "Winhttp.lib")

int wmain(int argc, WCHAR **argv) {
    URL_COMPONENTS parts = {0}; WCHAR scheme[16], host[256], path[2048], extra[2048];
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls URL\n", argv[0]); return 2; }
    parts.dwStructSize = sizeof(parts);
    parts.lpszScheme = scheme; parts.dwSchemeLength = ARRAYSIZE(scheme);
    parts.lpszHostName = host; parts.dwHostNameLength = ARRAYSIZE(host);
    parts.lpszUrlPath = path; parts.dwUrlPathLength = ARRAYSIZE(path);
    parts.lpszExtraInfo = extra; parts.dwExtraInfoLength = ARRAYSIZE(extra);
    if (!WinHttpCrackUrl(argv[1], 0, 0, &parts)) { fwprintf(stderr, L"Invalid URL (%lu).\n", GetLastError()); return 1; }
    wprintf(L"Scheme: %.*ls\nHost:   %.*ls\nPort:   %u\nPath:   %.*ls\nExtra:  %.*ls\n",
        parts.dwSchemeLength, parts.lpszScheme, parts.dwHostNameLength, parts.lpszHostName,
        parts.nPort, parts.dwUrlPathLength, parts.lpszUrlPath, parts.dwExtraInfoLength, parts.lpszExtraInfo);
    return 0;
}
