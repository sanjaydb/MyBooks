#define UNICODE
#define _UNICODE
#include <windows.h>
#include <winsvc.h>
#include <stdio.h>
#pragma comment(lib, "Advapi32.lib")

static const WCHAR *state_name(DWORD state) {
    switch (state) {
        case SERVICE_STOPPED: return L"Stopped";
        case SERVICE_START_PENDING: return L"Start pending";
        case SERVICE_STOP_PENDING: return L"Stop pending";
        case SERVICE_RUNNING: return L"Running";
        case SERVICE_CONTINUE_PENDING: return L"Continue pending";
        case SERVICE_PAUSE_PENDING: return L"Pause pending";
        case SERVICE_PAUSED: return L"Paused";
        default: return L"Unknown";
    }
}

int wmain(int argc, WCHAR **argv) {
    SC_HANDLE manager, service;
    SERVICE_STATUS_PROCESS status;
    DWORD bytesNeeded;
    if (argc != 2) {
        fwprintf(stderr, L"Usage: %ls SERVICE_NAME\nExample: %ls Spooler\n", argv[0], argv[0]);
        return 2;
    }
    manager = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
    if (!manager) { fwprintf(stderr, L"OpenSCManager failed (%lu).\n", GetLastError()); return 1; }
    service = OpenServiceW(manager, argv[1], SERVICE_QUERY_STATUS);
    if (!service) {
        fwprintf(stderr, L"OpenService failed (%lu).\n", GetLastError());
        CloseServiceHandle(manager); return 1;
    }
    if (!QueryServiceStatusEx(service, SC_STATUS_PROCESS_INFO, (BYTE *)&status,
                              sizeof(status), &bytesNeeded)) {
        fwprintf(stderr, L"QueryServiceStatusEx failed (%lu).\n", GetLastError());
        CloseServiceHandle(service); CloseServiceHandle(manager); return 1;
    }
    wprintf(L"Service: %ls\nState:   %ls\nPID:     %lu\n", argv[1],
            state_name(status.dwCurrentState), status.dwProcessId);
    CloseServiceHandle(service);
    CloseServiceHandle(manager);
    return 0;
}
