#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "User32.lib")

int wmain(void) {
    RECT workArea;
    int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int monitors = GetSystemMetrics(SM_CMONITORS);
    if (!SystemParametersInfoW(SPI_GETWORKAREA, 0, &workArea, 0)) {
        fwprintf(stderr, L"SystemParametersInfo failed (%lu).\n", GetLastError()); return 1;
    }
    wprintf(L"Monitor count:        %d\n", monitors);
    wprintf(L"Virtual desktop:      %d x %d pixels\n", width, height);
    wprintf(L"Primary work area:    %ld x %ld pixels\n",
            workArea.right - workArea.left, workArea.bottom - workArea.top);
    return 0;
}
