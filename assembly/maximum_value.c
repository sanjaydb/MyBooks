#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    int first = 41, second = 73, result;
    __asm {
        mov eax, first
        cmp eax, second
        jge selected
        mov eax, second
    selected:
        mov result, eax
    }
    printf("Maximum of %d and %d is %d\n", first, second, result);
    return 0;
}
