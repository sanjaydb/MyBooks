#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib, "Wininet.lib")

int wmain(int argc, WCHAR **argv) {
    HINTERNET session, request; HANDLE output; BYTE buffer[8192]; DWORD read, written; int result = 1;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls URL OUTPUT_FILE\n", argv[0]); return 2; }
    output = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (output == INVALID_HANDLE_VALUE) { fwprintf(stderr, L"Output exists or cannot be created (%lu).\n", GetLastError()); return 1; }
    session = InternetOpenW(L"SimpleInternetUtility/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    request = session ? InternetOpenUrlW(session, argv[1], NULL, 0, INTERNET_FLAG_NO_UI | INTERNET_FLAG_RELOAD, 0) : NULL;
    if (!request) goto cleanup;
    while (InternetReadFile(request, buffer, sizeof(buffer), &read) && read) {
        if (!WriteFile(output, buffer, read, &written, NULL) || written != read) goto cleanup;
    }
    result = 0; wprintf(L"Downloaded to: %ls\n", argv[2]);
cleanup:
    if (result) fwprintf(stderr, L"Download failed (%lu); the partial file remains.\n", GetLastError());
    if (request) InternetCloseHandle(request); if (session) InternetCloseHandle(session); CloseHandle(output); return result;
}
