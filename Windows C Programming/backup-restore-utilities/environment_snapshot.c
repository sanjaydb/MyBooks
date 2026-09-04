#define UNICODE
#define _UNICODE
#include <windows.h>
#include <stdio.h>

int wmain(int argc, WCHAR **argv) {
    const WCHAR *names[] = {L"USERNAME", L"COMPUTERNAME", L"USERPROFILE", L"APPDATA", L"LOCALAPPDATA", L"TEMP"};
    WCHAR value[32768]; FILE *output;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls OUTPUT_FILE\n", argv[0]); return 2; }
    if (_wfopen_s(&output, argv[1], L"w, ccs=UTF-8") != 0) { fwprintf(stderr, L"Unable to create output file.\n"); return 1; }
    for (size_t i = 0; i < ARRAYSIZE(names); ++i) {
        DWORD length = GetEnvironmentVariableW(names[i], value, ARRAYSIZE(value));
        fwprintf(output, L"%ls=%ls\n", names[i], length && length < ARRAYSIZE(value) ? value : L"");
    }
    fclose(output); wprintf(L"Environment snapshot created: %ls\n", argv[1]); return 0;
}
