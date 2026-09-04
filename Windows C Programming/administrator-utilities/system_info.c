#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    WCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD nameLength = ARRAYSIZE(computerName);
    SYSTEM_INFO info;
    const WCHAR *architecture = L"Unknown";

    if (!GetComputerNameW(computerName, &nameLength)) {
        fwprintf(stderr, L"GetComputerName failed (%lu).\n", GetLastError());
        return 1;
    }
    GetNativeSystemInfo(&info);
    switch (info.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64: architecture = L"x64"; break;
        case PROCESSOR_ARCHITECTURE_ARM64: architecture = L"ARM64"; break;
        case PROCESSOR_ARCHITECTURE_INTEL: architecture = L"x86"; break;
    }

    wprintf(L"Computer name: %ls\n", computerName);
    wprintf(L"Architecture:  %ls\n", architecture);
    wprintf(L"Processors:    %lu\n", info.dwNumberOfProcessors);
    wprintf(L"Page size:     %lu bytes\n", info.dwPageSize);
    return 0;
}
