#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    const char *text = "Windows 11";
    int result;
    __asm {
        mov esi, text
        xor ecx, ecx
    scan_next:
        cmp byte ptr [esi + ecx], 0
        je scan_done
        inc ecx
        jmp scan_next
    scan_done:
        mov result, ecx
    }
    printf("Length of \"%s\" = %d\n", text, result);
    return 0;
}
