#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    ULONGLONG seconds = GetTickCount64() / 1000;
    ULONGLONG days = seconds / 86400;
    unsigned long hours;
    unsigned long minutes;
    seconds %= 86400;
    hours = (unsigned long)(seconds / 3600);
    seconds %= 3600;
    minutes = (unsigned long)(seconds / 60);
    seconds %= 60;
    wprintf(L"System uptime: %llu days, %lu hours, %lu minutes, %llu seconds\n",
            days, hours, minutes, seconds);
    return 0;
}
