#include <stdio.h>
#include "shellcode_runner.h"
#ifndef _M_IX86
#error Build with the 32-bit x86 MSVC compiler.
#endif
typedef int (__cdecl *shell_fn)(void);
int main(void) {
    const unsigned char bytes[] = {0xB8, 0x2A, 0x00, 0x00, 0x00, 0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Returned: %d\n", ((shell_fn)code)());
    release_shellcode(code); return 0;
}
