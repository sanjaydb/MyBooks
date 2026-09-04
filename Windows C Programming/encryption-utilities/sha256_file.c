#define UNICODE
#define _UNICODE
#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>
#pragma comment(lib, "Bcrypt.lib")

int wmain(int argc, WCHAR **argv) {
    BCRYPT_ALG_HANDLE algorithm = NULL; BCRYPT_HASH_HANDLE hash = NULL; HANDLE file = INVALID_HANDLE_VALUE;
    BYTE buffer[8192], digest[32]; DWORD read; int result = 1;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls FILE\n", argv[0]); return 2; }
    if (BCryptOpenAlgorithmProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, NULL, 0) < 0 ||
        BCryptCreateHash(algorithm, &hash, NULL, 0, NULL, 0, 0) < 0) goto cleanup;
    file = CreateFileW(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (file == INVALID_HANDLE_VALUE) goto cleanup;
    for (;;) {
        if (!ReadFile(file, buffer, sizeof(buffer), &read, NULL)) goto cleanup;
        if (!read) break;
        if (BCryptHashData(hash, buffer, read, 0) < 0) goto cleanup;
    }
    if (BCryptFinishHash(hash, digest, sizeof(digest), 0) < 0) goto cleanup;
    for (DWORD i = 0; i < sizeof(digest); ++i) wprintf(L"%02x", digest[i]);
    wprintf(L"  %ls\n", argv[1]); result = 0;
cleanup:
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file); if (hash) BCryptDestroyHash(hash);
    if (algorithm) BCryptCloseAlgorithmProvider(algorithm, 0); return result;
}
