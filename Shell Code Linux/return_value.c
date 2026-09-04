#include <stdio.h>
#include "shellcode_runner.h"
#if !defined(__x86_64__)
#error Build this example on a 64-bit x86 Linux system.
#endif
typedef int (*shell_fn)(void);
int main(void) {
    const unsigned char bytes[] = {0xB8,0x2A,0x00,0x00,0x00,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Returned: %d\n", ((shell_fn)code)());
    release_shellcode(code, sizeof(bytes)); return 0;
}
