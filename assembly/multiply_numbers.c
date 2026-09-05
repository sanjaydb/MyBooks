#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    int value = -12, multiplier = 7, result;
    __asm {
        mov eax, value
        imul eax, multiplier
        mov result, eax
    }
    printf("%d * %d = %d\n", value, multiplier, result);
    return 0;
}
