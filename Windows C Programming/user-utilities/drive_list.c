#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#include <wchar.h>

static const WCHAR *drive_type(UINT type) {
    switch (type) {
        case DRIVE_REMOVABLE: return L"Removable";
        case DRIVE_FIXED: return L"Fixed";
        case DRIVE_REMOTE: return L"Network";
        case DRIVE_CDROM: return L"Optical";
        case DRIVE_RAMDISK: return L"RAM disk";
        default: return L"Unknown";
    }
}

int wmain(void) {
    WCHAR drives[512];
    DWORD length = GetLogicalDriveStringsW(ARRAYSIZE(drives), drives);
    if (length == 0 || length >= ARRAYSIZE(drives)) {
        fwprintf(stderr, L"GetLogicalDriveStrings failed (%lu).\n", GetLastError()); return 1;
    }
    wprintf(L"%-8ls %ls\n", L"DRIVE", L"TYPE");
    for (WCHAR *drive = drives; *drive; drive += wcslen(drive) + 1)
        wprintf(L"%-8ls %ls\n", drive, drive_type(GetDriveTypeW(drive)));
    return 0;
}
