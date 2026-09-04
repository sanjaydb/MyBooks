#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    int left = 50, right = 18, result;
    __asm {
        mov eax, left
        sub eax, right
        mov result, eax
    }
    printf("%d - %d = %d\n", left, right, result);
    return 0;
}
