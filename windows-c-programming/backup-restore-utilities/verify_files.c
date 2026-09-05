#define UNICODE
#define _UNICODE
#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib, "Bcrypt.lib")

static int hash_file(const WCHAR *path, BYTE hash[32]) {
    BCRYPT_ALG_HANDLE algorithm = NULL; BCRYPT_HASH_HANDLE hasher = NULL; HANDLE file = INVALID_HANDLE_VALUE;
    BYTE buffer[8192]; DWORD read; int ok = 0;
    if (BCryptOpenAlgorithmProvider(&algorithm, BCRYPT_SHA256_ALGORITHM, NULL, 0) < 0) goto done;
    if (BCryptCreateHash(algorithm, &hasher, NULL, 0, NULL, 0, 0) < 0) goto done;
    file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) goto done;
    for (;;) {
        if (!ReadFile(file, buffer, sizeof(buffer), &read, NULL)) goto done;
        if (!read) break;
        if (BCryptHashData(hasher, buffer, read, 0) < 0) goto done;
    }
    if (BCryptFinishHash(hasher, hash, 32, 0) >= 0) ok = 1;
done:
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file); if (hasher) BCryptDestroyHash(hasher);
    if (algorithm) BCryptCloseAlgorithmProvider(algorithm, 0); return ok;
}

int wmain(int argc, WCHAR **argv) {
    BYTE first[32], second[32];
    if (argc != 3) { fwprintf(stderr, L"Usage: %ls ORIGINAL BACKUP\n", argv[0]); return 2; }
    if (!hash_file(argv[1], first) || !hash_file(argv[2], second)) { fwprintf(stderr, L"Unable to hash one of the files.\n"); return 1; }
    if (memcmp(first, second, 32) == 0) { wprintf(L"MATCH: files have the same SHA-256 hash.\n"); return 0; }
    wprintf(L"DIFFERENT: files do not match.\n"); return 1;
}
