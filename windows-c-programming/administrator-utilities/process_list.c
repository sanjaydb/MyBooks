#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

int wmain(void) {
    HANDLE snapshot;
    PROCESSENTRY32W process = {0};
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        fwprintf(stderr, L"CreateToolhelp32Snapshot failed (%lu).\n", GetLastError());
        return 1;
    }
    process.dwSize = sizeof(process);
    if (!Process32FirstW(snapshot, &process)) {
        fwprintf(stderr, L"Process32First failed (%lu).\n", GetLastError());
        CloseHandle(snapshot);
        return 1;
    }
    wprintf(L"%-8ls %-8ls %ls\n", L"PID", L"PPID", L"PROCESS");
    do {
        wprintf(L"%-8lu %-8lu %ls\n", process.th32ProcessID,
                process.th32ParentProcessID, process.szExeFile);
    } while (Process32NextW(snapshot, &process));
    CloseHandle(snapshot);
    return 0;
}
