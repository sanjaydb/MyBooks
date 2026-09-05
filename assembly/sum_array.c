#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    int values[] = {3, 5, 7, 9, 11};
    int count = sizeof(values) / sizeof(values[0]), result;
    __asm {
        lea esi, values
        mov ecx, count
        xor eax, eax
    add_next:
        add eax, [esi]
        add esi, 4
        dec ecx
        jnz add_next
        mov result, eax
    }
    printf("Array sum = %d\n", result);
    return 0;
}
