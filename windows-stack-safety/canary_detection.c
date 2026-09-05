#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char buffer[16];
    uint32_t sentinel;
} guarded_buffer;

static int store_text(guarded_buffer *guarded, const char *text) {
    guarded->sentinel = UINT32_C(0xA5B6C7D8);
    if (strcpy_s(guarded->buffer, sizeof(guarded->buffer), text) != 0) return 0;
    return guarded->sentinel == UINT32_C(0xA5B6C7D8);
}

int main(void) {
    guarded_buffer guarded = {{0}, 0};
    if (!store_text(&guarded, "safe text")) { fprintf(stderr, "Copy rejected or sentinel changed.\n"); return 1; }
    printf("Stored: %s\nSentinel unchanged: 0x%08X\n", guarded.buffer, guarded.sentinel);
    return 0;
}
