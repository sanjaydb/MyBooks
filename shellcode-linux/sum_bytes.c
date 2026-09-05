#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef unsigned int (*shell_fn)(const unsigned char *, unsigned int);
int main(void) {
    const unsigned char bytes[] = {
        0x31,0xC0, 0x85,0xF6, 0x74,0x0C, 0x0F,0xB6,0x17,
        0x01,0xD0, 0x48,0xFF,0xC7, 0xFF,0xCE, 0x75,0xF4, 0xC3
    };
    const unsigned char values[] = {1, 2, 3, 4, 5};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Byte sum = %u\n", ((shell_fn)code)(values, sizeof(values)));
    release_shellcode(code, sizeof(bytes)); return 0;
}
