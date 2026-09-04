#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(void) {
    SECURITY_ATTRIBUTES security = {sizeof(security), NULL, TRUE};
    HANDLE readPipe, writePipe; STARTUPINFOW startup = {0}; PROCESS_INFORMATION process = {0};
    WCHAR command[] = L"cmd.exe /d /c echo Hello from the child process";
    char buffer[256]; DWORD bytesRead;
    if (!CreatePipe(&readPipe, &writePipe, &security, 0)) return 1;
    SetHandleInformation(readPipe, HANDLE_FLAG_INHERIT, 0);
    startup.cb = sizeof(startup); startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdOutput = writePipe; startup.hStdError = writePipe; startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    if (!CreateProcessW(NULL, command, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startup, &process)) {
        fwprintf(stderr, L"CreateProcess failed (%lu).\n", GetLastError()); CloseHandle(readPipe); CloseHandle(writePipe); return 1;
    }
    CloseHandle(writePipe);
    while (ReadFile(readPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead)
        fwrite(buffer, 1, bytesRead, stdout);
    WaitForSingleObject(process.hProcess, INFINITE);
    CloseHandle(readPipe); CloseHandle(process.hThread); CloseHandle(process.hProcess); return 0;
}
