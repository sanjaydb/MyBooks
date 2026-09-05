#include <stdio.h>
#include "shellcode_runner.h"
#ifndef _M_IX86
#error Build with the 32-bit x86 MSVC compiler.
#endif
typedef unsigned int (__cdecl *shell_fn)(const unsigned char *, unsigned int);
int main(void) {
    const unsigned char bytes[] = {
        0x53, 0x8B,0x54,0x24,0x08, 0x8B,0x4C,0x24,0x0C,
        0x31,0xC0, 0x85,0xC9, 0x74,0x09, 0x0F,0xB6,0x1A,
        0x01,0xD8, 0x42, 0x49, 0x75,0xF7, 0x5B, 0xC3
    };
    const unsigned char values[] = {1, 2, 3, 4, 5};
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Byte sum = %u\n", ((shell_fn)code)(values, sizeof(values)));
    release_shellcode(code); return 0;
}
