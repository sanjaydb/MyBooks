#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char destination[16];
    if (argc != 2) { fprintf(stderr, "Usage: %s TEXT\n", argv[0]); return 2; }
    if (strlen(argv[1]) >= sizeof(destination)) {
        fprintf(stderr, "Input rejected: maximum length is %zu characters.\n", sizeof(destination) - 1);
        return 1;
    }
    if (strcpy_s(destination, sizeof(destination), argv[1]) != 0) return 1;
    printf("Copied safely: %s\n", destination);
    return 0;
}
