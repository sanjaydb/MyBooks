#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

static void print_variable(const WCHAR *name) {
    WCHAR value[32768];
    DWORD length = GetEnvironmentVariableW(name, value, ARRAYSIZE(value));
    if (length > 0 && length < ARRAYSIZE(value)) wprintf(L"%-14ls %ls\n", name, value);
    else wprintf(L"%-14ls (not set)\n", name);
}

int wmain(void) {
    static const WCHAR *names[] = {
        L"USERNAME", L"USERPROFILE", L"HOMEDRIVE", L"HOMEPATH",
        L"TEMP", L"APPDATA", L"LOCALAPPDATA", L"COMPUTERNAME"
    };
    for (size_t i = 0; i < ARRAYSIZE(names); ++i) print_variable(names[i]);
    return 0;
}
