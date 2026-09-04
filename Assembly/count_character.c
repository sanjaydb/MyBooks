#include <stdio.h>
#ifndef _M_IX86
#error Build this example with the 32-bit x86 MSVC compiler.
#endif
int main(void) {
    const char *text = "assembly examples";
    char wanted = 'e';
    int result;
    __asm {
        mov esi, text
        mov dl, wanted
        xor ecx, ecx
    check_next:
        mov al, [esi]
        test al, al
        jz count_done
        cmp al, dl
        jne not_match
        inc ecx
    not_match:
        inc esi
        jmp check_next
    count_done:
        mov result, ecx
    }
    printf("'%c' appears %d times in \"%s\"\n", wanted, result, text);
    return 0;
}
