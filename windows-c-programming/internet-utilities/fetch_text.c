#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib, "Wininet.lib")

int wmain(int argc, WCHAR **argv) {
    HINTERNET session, request; char buffer[4097]; DWORD bytesRead, total = 0; const DWORD limit = 1024 * 1024;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls URL\n", argv[0]); return 2; }
    session = InternetOpenW(L"SimpleInternetUtility/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!session) return 1;
    request = InternetOpenUrlW(session, argv[1], NULL, 0, INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD, 0);
    if (!request) { InternetCloseHandle(session); return 1; }
    while (total < limit && InternetReadFile(request, buffer, min(4096, limit - total), &bytesRead) && bytesRead) {
        fwrite(buffer, 1, bytesRead, stdout); total += bytesRead;
    }
    if (total == limit) fwprintf(stderr, L"\nOutput stopped at 1 MiB.\n");
    InternetCloseHandle(request); InternetCloseHandle(session); return 0;
}
