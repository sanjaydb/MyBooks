#include <windows.h>
#include <stdio.h>

static void release_buffer(HANDLE heap, unsigned char **buffer) {
    if (buffer && *buffer) { HeapFree(heap, 0, *buffer); *buffer = NULL; }
}
int main(void) {
    HANDLE heap = GetProcessHeap(); unsigned char *buffer = HeapAlloc(heap, HEAP_ZERO_MEMORY, 64);
    if (!buffer) return 1;
    buffer[0] = 42; printf("Value before release: %u\n", buffer[0]);
    release_buffer(heap, &buffer); release_buffer(heap, &buffer);
    printf("Pointer is null after release; repeated cleanup is harmless.\n"); return 0;
}
