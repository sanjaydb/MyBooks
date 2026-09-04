#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static HANDLE semaphore;
static DWORD WINAPI worker(LPVOID parameter) {
    int id = (int)(INT_PTR)parameter;
    WaitForSingleObject(semaphore, INFINITE);
    wprintf(L"Worker %d entered\n", id); Sleep(1000);
    wprintf(L"Worker %d leaving\n", id); ReleaseSemaphore(semaphore, 1, NULL); return 0;
}

int wmain(void) {
    HANDLE threads[4];
    semaphore = CreateSemaphoreW(NULL, 2, 2, L"Local\\SimpleIpcSemaphore");
    if (!semaphore) return 1;
    for (int i = 0; i < 4; ++i) threads[i] = CreateThread(NULL, 0, worker, (LPVOID)(INT_PTR)(i + 1), 0, NULL);
    if (WaitForMultipleObjects(4, threads, TRUE, INFINITE) == WAIT_FAILED) return 1;
    for (int i = 0; i < 4; ++i) CloseHandle(threads[i]);
    CloseHandle(semaphore); return 0;
}
