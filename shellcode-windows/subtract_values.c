#include <stdio.h>
#include "shellcode_runner.h"
#ifndef _M_IX86
#error Build with the 32-bit x86 MSVC compiler.
#endif
typedef int (__cdecl *shell_fn)(int, int);
int main(void) {
    const unsigned char bytes[] = {0x8B,0x44,0x24,0x04,0x2B,0x44,0x24,0x08,0xC3};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("50 - 8 = %d\n", ((shell_fn)code)(50, 8));
    release_shellcode(code); return 0;
}
