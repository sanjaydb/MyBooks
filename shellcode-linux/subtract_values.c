#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef int (*shell_fn)(int, int);
int main(void) {
    const unsigned char bytes[] = {0x89,0xF8,0x29,0xF0,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("50 - 8 = %d\n", ((shell_fn)code)(50, 8));
    release_shellcode(code, sizeof(bytes)); return 0;
}
