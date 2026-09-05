#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Crypt32.lib")

int wmain(int argc, WCHAR **argv) {
    HANDLE in, out; LARGE_INTEGER size; char *text; BYTE *decoded; DWORD read, needed = 0, written;
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls BASE64_FILE NEW_OUTPUT_FILE\n", argv[0]); return 2; }
    in = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (in == INVALID_HANDLE_VALUE || !GetFileSizeEx(in, &size) || size.QuadPart > 32 * 1024 * 1024) { if (in != INVALID_HANDLE_VALUE) CloseHandle(in); return 1; }
    text = malloc((size_t)size.QuadPart + 1); if (!text || !ReadFile(in, text, (DWORD)size.QuadPart, &read, NULL)) { free(text); CloseHandle(in); return 1; }
    text[read] = '\0';
    if (!CryptStringToBinaryA(text, 0, CRYPT_STRING_BASE64, NULL, &needed, NULL, NULL)) { free(text); CloseHandle(in); return 1; }
    decoded = malloc(needed ? needed : 1);
    if (!decoded || !CryptStringToBinaryA(text, 0, CRYPT_STRING_BASE64, decoded, &needed, NULL, NULL)) { free(decoded); free(text); CloseHandle(in); return 1; }
    out = CreateFileW(argv[2], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (out == INVALID_HANDLE_VALUE || !WriteFile(out, decoded, needed, &written, NULL)) { if (out != INVALID_HANDLE_VALUE) CloseHandle(out); free(decoded); free(text); CloseHandle(in); return 1; }
    CloseHandle(out); free(decoded); free(text); CloseHandle(in); return 0;
}
