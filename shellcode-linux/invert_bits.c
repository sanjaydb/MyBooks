#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef unsigned int (*shell_fn)(unsigned int);
int main(void) {
    const unsigned char bytes[] = {0x89,0xF8,0xF7,0xD0,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("NOT 0x0000FFFF = 0x%08X\n", ((shell_fn)code)(0x0000FFFF));
    release_shellcode(code, sizeof(bytes)); return 0;
}
