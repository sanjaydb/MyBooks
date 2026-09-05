#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static void print_time(const WCHAR *label, const SYSTEMTIME *time) {
    wprintf(L"%-7ls %04u-%02u-%02u %02u:%02u:%02u\n", label,
            time->wYear, time->wMonth, time->wDay,
            time->wHour, time->wMinute, time->wSecond);
}

int wmain(void) {
    SYSTEMTIME local, utc;
    TIME_ZONE_INFORMATION zone;
    DWORD result;
    GetLocalTime(&local);
    GetSystemTime(&utc);
    result = GetTimeZoneInformation(&zone);
    if (result == TIME_ZONE_ID_INVALID) {
        fwprintf(stderr, L"GetTimeZoneInformation failed (%lu).\n", GetLastError()); return 1;
    }
    print_time(L"Local:", &local);
    print_time(L"UTC:", &utc);
    wprintf(L"Zone:   %ls\n", result == TIME_ZONE_ID_DAYLIGHT ? zone.DaylightName : zone.StandardName);
    return 0;
}
