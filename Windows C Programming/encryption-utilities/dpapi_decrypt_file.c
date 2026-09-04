#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Crypt32.lib")

int wmain(int argc, WCHAR **argv) {
    HANDLE in, out; LARGE_INTEGER size; BYTE *buffer = NULL; DWORD read, written; DATA_BLOB cipher, plain = {0}; int result = 1;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls ENCRYPTED_FILE NEW_OUTPUT_FILE\n", argv[0]); return 2; }
    in = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (in == INVALID_HANDLE_VALUE || !GetFileSizeEx(in, &size) || size.QuadPart > 64 * 1024 * 1024) { fwprintf(stderr, L"Input is unavailable or too large.\n"); if (in != INVALID_HANDLE_VALUE) CloseHandle(in); return 1; }
    buffer = malloc((size_t)(size.QuadPart ? size.QuadPart : 1));
    if (!buffer || !ReadFile(in, buffer, (DWORD)size.QuadPart, &read, NULL)) goto cleanup;
    cipher.pbData = buffer; cipher.cbData = read;
    if (!CryptUnprotectData(&cipher, NULL, NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &plain)) goto cleanup;
    out = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (out == INVALID_HANDLE_VALUE) goto cleanup;
    result = WriteFile(out, plain.pbData, plain.cbData, &written, NULL) && written == plain.cbData ? 0 : 1; CloseHandle(out);
cleanup:
    if (result) fwprintf(stderr, L"Decryption failed (%lu). Existing output was not overwritten.\n", GetLastError());
    if (plain.pbData) LocalFree(plain.pbData); free(buffer); CloseHandle(in); return result;
}
