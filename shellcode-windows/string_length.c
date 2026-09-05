#include <stdio.h>
#include "shellcode_runner.h"
#ifndef _M_IX86
#error Build with the 32-bit x86 MSVC compiler.
#endif
typedef unsigned int (__cdecl *shell_fn)(const char *);
int main(void) {
    const unsigned char bytes[] = {
        0x8B,0x54,0x24,0x04, 0x31,0xC0, 0x80,0x3C,0x02,0x00,
        0x74,0x03, 0x40, 0xEB,0xF7, 0xC3
    };
    const char text[] = "Windows shellcode";
    void *code = prepare_shellcode(bytes, sizeof(bytes));
    if (!code) return 1;
    printf("Length of \"%s\" = %u\n", text, ((shell_fn)code)(text));
    release_shellcode(code); return 0;
}
