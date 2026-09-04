#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    char vendor[13] = {0};
    __asm {
        xor eax, eax
        cpuid
        mov dword ptr vendor[0], ebx
        mov dword ptr vendor[4], edx
        mov dword ptr vendor[8], ecx
    }
    printf("CPU vendor: %s\n", vendor);
    return 0;
}
