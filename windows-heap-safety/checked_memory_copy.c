#include <windows.h>
#include <stdio.h>
#include <string.h>

static int copy_bytes(void *destination, size_t capacity, const void *source, size_t count) {
    if (!destination || !source || count > capacity) return 0;
    memcpy(destination, source, count); return 1;
}
int main(void) {
    const unsigned char source[] = {1, 2, 3, 4, 5}; HANDLE heap = GetProcessHeap();
    unsigned char *destination = HeapAlloc(heap, HEAP_ZERO_MEMORY, sizeof(source));
    if (!destination || !copy_bytes(destination, sizeof(source), source, sizeof(source))) return 1;
    printf("Copied %zu bytes safely; last byte is %u.\n", sizeof(source), destination[4]);
    HeapFree(heap, 0, destination); return 0;
}
