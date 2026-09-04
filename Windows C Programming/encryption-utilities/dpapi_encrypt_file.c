#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Crypt32.lib")

int wmain(int argc, WCHAR **argv) {
    HANDLE in, out; LARGE_INTEGER size; BYTE *buffer = NULL; DWORD read, written; DATA_BLOB plain, cipher = {0}; int result = 1;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls INPUT_FILE NEW_ENCRYPTED_FILE\n", argv[0]); return 2; }
    in = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (in == INVALID_HANDLE_VALUE || !GetFileSizeEx(in, &size) || size.QuadPart > 64 * 1024 * 1024) { fwprintf(stderr, L"Input must be a readable file no larger than 64 MiB.\n"); if (in != INVALID_HANDLE_VALUE) CloseHandle(in); return 1; }
    buffer = malloc((size_t)(size.QuadPart ? size.QuadPart : 1));
    if (!buffer || !ReadFile(in, buffer, (DWORD)size.QuadPart, &read, NULL)) goto cleanup;
    plain.pbData = buffer; plain.cbData = read;
    if (!CryptProtectData(&plain, L"Simple protected file", NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &cipher)) goto cleanup;
    out = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (out == INVALID_HANDLE_VALUE) goto cleanup;
    result = WriteFile(out, cipher.pbData, cipher.cbData, &written, NULL) && written == cipher.cbData ? 0 : 1; CloseHandle(out);
cleanup:
    if (result) fwprintf(stderr, L"Encryption failed (%lu). Existing output was not overwritten.\n", GetLastError());
    if (cipher.pbData) LocalFree(cipher.pbData); free(buffer); CloseHandle(in); return result;
}
