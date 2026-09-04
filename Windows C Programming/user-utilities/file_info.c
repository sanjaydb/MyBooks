#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static void print_time(const WCHAR *label, const FILETIME *utc) {
    FILETIME local;
    SYSTEMTIME time;
    if (FileTimeToLocalFileTime(utc, &local) && FileTimeToSystemTime(&local, &time))
        wprintf(L"%-12ls %04u-%02u-%02u %02u:%02u:%02u\n", label,
                time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
}

int wmain(int argc, WCHAR **argv) {
    WIN32_FILE_ATTRIBUTE_DATA info;
    ULARGE_INTEGER size;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls FILE\n", argv[0]); return 2; }
    if (!GetFileAttributesExW(argv[1], GetFileExInfoStandard, &info)) {
        fwprintf(stderr, L"Unable to read file information (%lu).\n", GetLastError()); return 1;
    }
    if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        fwprintf(stderr, L"The supplied path is a directory, not a file.\n"); return 2;
    }
    size.HighPart = info.nFileSizeHigh; size.LowPart = info.nFileSizeLow;
    wprintf(L"File:        %ls\nSize:        %llu bytes\n", argv[1], size.QuadPart);
    print_time(L"Created:", &info.ftCreationTime);
    print_time(L"Modified:", &info.ftLastWriteTime);
    print_time(L"Accessed:", &info.ftLastAccessTime);
    return 0;
}
