#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static DWORD WINAPI wait_for_event(LPVOID parameter) {
    HANDLE event = (HANDLE)parameter;
    wprintf(L"Worker is waiting for the event...\n");
    WaitForSingleObject(event, INFINITE);
    wprintf(L"Worker received the event signal.\n"); return 0;
}

int wmain(void) {
    HANDLE event = CreateEventW(NULL, TRUE, FALSE, L"Local\\SimpleIpcEvent");
    HANDLE thread;
    if (!event) return 1;
    thread = CreateThread(NULL, 0, wait_for_event, event, 0, NULL);
    if (!thread) { CloseHandle(event); return 1; }
    Sleep(1000); wprintf(L"Main thread is signaling the event.\n"); SetEvent(event);
    WaitForSingleObject(thread, INFINITE); CloseHandle(thread); CloseHandle(event); return 0;
}
