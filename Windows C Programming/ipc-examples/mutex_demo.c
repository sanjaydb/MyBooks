#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    HANDLE mutex = CreateMutexW(NULL, FALSE, L"Local\\SimpleIpcMutex");
    DWORD waitResult;
    if (!mutex) { fwprintf(stderr, L"CreateMutex failed (%lu).\n", GetLastError()); return 1; }
    wprintf(L"Waiting for the named mutex...\n");
    waitResult = WaitForSingleObject(mutex, 10000);
    if (waitResult != WAIT_OBJECT_0 && waitResult != WAIT_ABANDONED) {
        fwprintf(stderr, L"The mutex was not acquired.\n"); CloseHandle(mutex); return 1;
    }
    wprintf(L"Mutex acquired for 3 seconds. Start another copy to see it wait.\n");
    Sleep(3000); ReleaseMutex(mutex); CloseHandle(mutex); return 0;
}
