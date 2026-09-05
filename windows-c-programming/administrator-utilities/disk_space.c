#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static double to_gib(ULONGLONG bytes) { return (double)bytes / (1024.0 * 1024.0 * 1024.0); }

int wmain(int argc, WCHAR **argv) {
    const WCHAR *path = argc > 1 ? argv[1] : L"C:\\";
    ULARGE_INTEGER available, total, freeBytes;
    if (argc > 2) {
        fwprintf(stderr, L"Usage: %ls [drive-or-path]\n", argv[0]);
        return 2;
    }
    if (!GetDiskFreeSpaceExW(path, &available, &total, &freeBytes)) {
        fwprintf(stderr, L"GetDiskFreeSpaceEx failed for %ls (%lu).\n", path, GetLastError());
        return 1;
    }
    wprintf(L"Path:                 %ls\n", path);
    wprintf(L"Total space:          %.2f GiB\n", to_gib(total.QuadPart));
    wprintf(L"Free space:           %.2f GiB\n", to_gib(freeBytes.QuadPart));
    wprintf(L"Available to caller:  %.2f GiB\n", to_gib(available.QuadPart));
    return 0;
}
