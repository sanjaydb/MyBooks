#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "User32.lib")

int wmain(void) {
    HANDLE data;
    const WCHAR *text;
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) {
        wprintf(L"The clipboard does not contain Unicode text.\n");
        return 0;
    }
    if (!OpenClipboard(NULL)) {
        fwprintf(stderr, L"OpenClipboard failed (%lu).\n", GetLastError());
        return 1;
    }
    data = GetClipboardData(CF_UNICODETEXT);
    if (!data) {
        fwprintf(stderr, L"GetClipboardData failed (%lu).\n", GetLastError());
        CloseClipboard();
        return 1;
    }
    text = GlobalLock(data);
    if (!text) {
        fwprintf(stderr, L"GlobalLock failed (%lu).\n", GetLastError());
        CloseClipboard();
        return 1;
    }
    wprintf(L"%ls\n", text);
    GlobalUnlock(data);
    CloseClipboard();
    return 0;
}
