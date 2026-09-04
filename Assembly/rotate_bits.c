#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    unsigned int value = 0x12345678U, result;
    unsigned char positions = 8;
    __asm {
        mov eax, value
        mov cl, positions
        rol eax, cl
        mov result, eax
    }
    printf("Rotate 0x%08X left by %u = 0x%08X\n", value, positions, result);
    return 0;
}
