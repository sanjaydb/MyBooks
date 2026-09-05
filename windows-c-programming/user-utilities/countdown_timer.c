#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wchar.h>

int wmain(int argc, WCHAR **argv) {
    WCHAR *end;
    unsigned long seconds;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls SECONDS\n", argv[0]); return 2; }
    errno = 0;
    seconds = wcstoul(argv[1], &end, 10);
    if (errno || *end != L'\0' || seconds == 0 || seconds > 86400) {
        fwprintf(stderr, L"Seconds must be from 1 to 86400.\n"); return 2;
    }
    while (seconds > 0) {
        wprintf(L"\rTime remaining: %lu second%ls  ", seconds, seconds == 1 ? L"" : L"s");
        fflush(stdout);
        Sleep(1000);
        --seconds;
    }
    wprintf(L"\rTime is up!                         \n");
    Beep(750, 300);
    return 0;
}
