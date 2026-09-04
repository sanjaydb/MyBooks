#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv) {
    const unsigned char *text;
    if (argc != 2) { fprintf(stderr, "Usage: %s TEXT\n", argv[0]); return 2; }
    text = (const unsigned char *)argv[1];
    while (*text) {
        if (isalnum(*text) || *text == '-' || *text == '_' || *text == '.' || *text == '~') putchar(*text);
        else printf("%%%02X", *text);
        ++text;
    }
    putchar('\n'); return 0;
}
