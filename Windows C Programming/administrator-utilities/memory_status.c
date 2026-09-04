#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static double to_gib(DWORDLONG bytes) { return (double)bytes / (1024.0 * 1024.0 * 1024.0); }

int wmain(void) {
    MEMORYSTATUSEX memory = {0};
    memory.dwLength = sizeof(memory);
    if (!GlobalMemoryStatusEx(&memory)) {
        fwprintf(stderr, L"GlobalMemoryStatusEx failed (%lu).\n", GetLastError());
        return 1;
    }
    wprintf(L"Memory load:                %lu%%\n", memory.dwMemoryLoad);
    wprintf(L"Physical memory total:      %.2f GiB\n", to_gib(memory.ullTotalPhys));
    wprintf(L"Physical memory available:  %.2f GiB\n", to_gib(memory.ullAvailPhys));
    wprintf(L"Virtual memory total:       %.2f GiB\n", to_gib(memory.ullTotalVirtual));
    wprintf(L"Virtual memory available:   %.2f GiB\n", to_gib(memory.ullAvailVirtual));
    return 0;
}
