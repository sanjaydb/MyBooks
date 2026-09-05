#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef unsigned int (*shell_fn)(unsigned int, unsigned int);
int main(void) {
    const unsigned char bytes[] = {0x89,0xF8,0x31,0xF0,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("0xAA55 XOR 0x0FF0 = 0x%X\n", ((shell_fn)code)(0xAA55, 0x0FF0));
    release_shellcode(code, sizeof(bytes)); return 0;
}
