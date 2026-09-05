#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    HANDLE file; LARGE_INTEGER size; ULARGE_INTEGER available, total, freeBytes;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls SOURCE_FILE DESTINATION_DIRECTORY\n", argv[0]); return 2; }
    file = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE || !GetFileSizeEx(file, &size)) { fwprintf(stderr, L"Unable to read source size.\n"); if (file != INVALID_HANDLE_VALUE) CloseHandle(file); return 1; }
    CloseHandle(file);
    if (!GetDiskFreeSpaceExW(argv[2], &available, &total, &freeBytes)) { fwprintf(stderr, L"Unable to read destination space (%lu).\n", GetLastError()); return 1; }
    wprintf(L"Source size: %lld bytes\nAvailable:   %llu bytes\nResult:      %ls\n", size.QuadPart, available.QuadPart,
            available.QuadPart >= (ULONGLONG)size.QuadPart ? L"Enough space" : L"Not enough space");
    return available.QuadPart >= (ULONGLONG)size.QuadPart ? 0 : 1;
}
