#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    int dividend = 100, divisor = 9, quotient, remainder;
    __asm {
        mov eax, dividend
        cdq
        idiv divisor
        mov quotient, eax
        mov remainder, edx
    }
    printf("%d / %d = %d, remainder %d\n", dividend, divisor, quotient, remainder);
    return 0;
}
