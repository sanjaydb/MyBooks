#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char name[32];
    if (argc != 2) { fprintf(stderr, "Usage: %s NAME\n", argv[0]); return 2; }
    if (strcpy_s(name, sizeof(name), argv[1]) != 0) {
        fprintf(stderr, "Name is too long; maximum is %zu characters.\n", sizeof(name) - 1);
        return 1;
    }
    printf("Hello, %s!\n", name);
    return 0;
}
