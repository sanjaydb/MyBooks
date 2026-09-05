#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Crypt32.lib")

int wmain(int argc, WCHAR **argv) {
    HANDLE in, out; LARGE_INTEGER size; BYTE *data; char *encoded; DWORD read, needed = 0, written;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls INPUT_FILE NEW_OUTPUT.txt\n", argv[0]); return 2; }
    in = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (in == INVALID_HANDLE_VALUE || !GetFileSizeEx(in, &size) || size.QuadPart > 16 * 1024 * 1024) { if (in != INVALID_HANDLE_VALUE) CloseHandle(in); return 1; }
    data = malloc((size_t)(size.QuadPart ? size.QuadPart : 1));
    if (!data || !ReadFile(in, data, (DWORD)size.QuadPart, &read, NULL)) { free(data); CloseHandle(in); return 1; }
    CryptBinaryToStringA(data, read, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &needed);
    encoded = malloc(needed); if (!encoded || !CryptBinaryToStringA(data, read, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encoded, &needed)) { free(encoded); free(data); CloseHandle(in); return 1; }
    out = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (out == INVALID_HANDLE_VALUE || !WriteFile(out, encoded, needed - 1, &written, NULL)) { if (out != INVALID_HANDLE_VALUE) CloseHandle(out); free(encoded); free(data); CloseHandle(in); return 1; }
    CloseHandle(out); free(encoded); free(data); CloseHandle(in); return 0;
}
