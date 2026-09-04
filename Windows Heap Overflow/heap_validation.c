#include <windows.h>
#include <stdio.h>

int main(void) {
    HANDLE heap = HeapCreate(0, 0, 0); unsigned char *buffer;
    if (!heap) return 1;
    buffer = HeapAlloc(heap, HEAP_ZERO_MEMORY, 128); if (!buffer) { HeapDestroy(heap); return 1; }
    for (size_t i = 0; i < 128; ++i) buffer[i] = (unsigned char)i;
    printf("Private heap validation: %s\n", HeapValidate(heap, 0, NULL) ? "passed" : "failed");
    HeapFree(heap, 0, buffer); HeapDestroy(heap); return 0;
}
