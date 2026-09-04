#include <stdio.h>
#include "shellcode_runner.h"
#ifndef _M_IX86
#error Build with the 32-bit x86 MSVC compiler.
#endif
typedef unsigned int (__cdecl *shell_fn)(unsigned int);
int main(void) {
    const unsigned char bytes[] = {0x8B,0x44,0x24,0x04,0xF7,0xD0,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("NOT 0x0000FFFF = 0x%08X\n", ((shell_fn)code)(0x0000FFFF));
    release_shellcode(code); return 0;
}
