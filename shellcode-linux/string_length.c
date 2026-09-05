#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef unsigned long (*shell_fn)(const char *);
int main(void) {
    const unsigned char bytes[] = {
        0x31,0xC0, 0x80,0x3C,0x07,0x00, 0x74,0x05,
        0x48,0xFF,0xC0, 0xEB,0xF5, 0xC3
    };
    const char text[] = "Linux shellcode";
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Length of \"%s\" = %lu\n", text, ((shell_fn)code)(text));
    release_shellcode(code, sizeof(bytes)); return 0;
}
