#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef int (*shell_fn)(int, int);
int main(void) {
    const unsigned char bytes[] = {0x89,0xF8,0x39,0xF7,0x7D,0x02,0x89,0xF0,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Maximum of -3 and 12 = %d\n", ((shell_fn)code)(-3, 12));
    release_shellcode(code, sizeof(bytes)); return 0;
}
