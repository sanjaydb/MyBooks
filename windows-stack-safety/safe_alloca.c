#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

int main(int argc, char **argv) {
    char *end; unsigned long requested; unsigned char *buffer;
    if (argc != 2) { fprintf(stderr, "Usage: %s BYTE_COUNT\n", argv[0]); return 2; }
    errno = 0; requested = strtoul(argv[1], &end, 10);
    if (errno || *end || requested < 1 || requested > 16384) {
        fprintf(stderr, "Byte count must be from 1 to 16384.\n"); return 2;
    }
    buffer = _malloca(requested);
    if (!buffer) return 1;
    for (unsigned long i = 0; i < requested; ++i) buffer[i] = 0;
    printf("Safely allocated and initialized %lu temporary bytes.\n", requested);
    _freea(buffer); return 0;
}
