#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <wchar.h>
#pragma comment(lib, "Crypt32.lib")

int wmain(int argc, WCHAR **argv) {
    DATA_BLOB plain, cipher = {0}; HANDLE file; DWORD written;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls TEXT NEW_OUTPUT.bin\n", argv[0]); return 2; }
    plain.pbData = (BYTE *)argv[1]; plain.cbData = (DWORD)((wcslen(argv[1]) + 1) * sizeof(WCHAR));
    if (!CryptProtectData(&plain, L"Simple protected text", NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &cipher)) return 1;
    file = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) { LocalFree(cipher.pbData); return 1; }
    if (!WriteFile(file, cipher.pbData, cipher.cbData, &written, NULL) || written != cipher.cbData) { CloseHandle(file); LocalFree(cipher.pbData); return 1; }
    wprintf(L"Protected text written to: %ls\n", argv[2]); CloseHandle(file); LocalFree(cipher.pbData); return 0;
}
