#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Crypt32.lib")

int wmain(int argc, WCHAR **argv) {
    HANDLE file; LARGE_INTEGER size; BYTE *buffer; DWORD read; DATA_BLOB cipher, plain = {0};
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls PROTECTED_TEXT.bin\n", argv[0]); return 2; }
    file = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (file == INVALID_HANDLE_VALUE || !GetFileSizeEx(file, &size) || size.QuadPart > 1024 * 1024) { if (file != INVALID_HANDLE_VALUE) CloseHandle(file); return 1; }
    buffer = malloc((size_t)size.QuadPart); if (!buffer) { CloseHandle(file); return 1; }
    if (!ReadFile(file, buffer, (DWORD)size.QuadPart, &read, NULL)) { free(buffer); CloseHandle(file); return 1; }
    cipher.pbData = buffer; cipher.cbData = read;
    if (!CryptUnprotectData(&cipher, NULL, NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &plain)) { free(buffer); CloseHandle(file); return 1; }
    wprintf(L"Recovered text: %ls\n", (WCHAR *)plain.pbData);
    LocalFree(plain.pbData); free(buffer); CloseHandle(file); return 0;
}
