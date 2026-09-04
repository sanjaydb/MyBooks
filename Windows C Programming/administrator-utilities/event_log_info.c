#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "Advapi32.lib")

int wmain(int argc, WCHAR **argv) {
    const WCHAR *logName = argc > 1 ? argv[1] : L"System";
    HANDLE log;
    DWORD records, oldest;
    if (argc > 2) {
        fwprintf(stderr, L"Usage: %ls [log-name]\nExample: %ls Application\n", argv[0], argv[0]);
        return 2;
    }
    log = OpenEventLogW(NULL, logName);
    if (!log) { fwprintf(stderr, L"OpenEventLog failed (%lu).\n", GetLastError()); return 1; }
    if (!GetNumberOfEventLogRecords(log, &records) ||
        !GetOldestEventLogRecord(log, &oldest)) {
        fwprintf(stderr, L"Unable to query the event log (%lu).\n", GetLastError());
        CloseEventLog(log); return 1;
    }
    wprintf(L"Event log:     %ls\n", logName);
    wprintf(L"Record count:  %lu\n", records);
    wprintf(L"Oldest record: %lu\n", oldest);
    CloseEventLog(log);
    return 0;
}
