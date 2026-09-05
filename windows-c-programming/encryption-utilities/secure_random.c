#define UNICODE
#define _UNICODE
#include <windows.h>
#include <bcrypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#pragma comment(lib, "Bcrypt.lib")

int wmain(int argc, WCHAR **argv) {
    WCHAR *end; unsigned long count; BYTE *bytes;
    if (argc != 2) { fwprintf(stderr, L"Usage: %ls BYTE_COUNT (1-4096)\n", argv[0]); return 2; }
    count = wcstoul(argv[1], &end, 10);
    if (*end || count < 1 || count > 4096) { fwprintf(stderr, L"Byte count must be from 1 to 4096.\n"); return 2; }
    bytes = malloc(count); if (!bytes) return 1;
    if (BCryptGenRandom(NULL, bytes, count, BCRYPT_USE_SYSTEM_PREFERRED_RNG) < 0) { free(bytes); return 1; }
    for (unsigned long i = 0; i < count; ++i) printf("%02x", bytes[i]);
    printf("\n"); SecureZeroMemory(bytes, count); free(bytes); return 0;
}
