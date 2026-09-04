#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void) {
    const size_t capacity = 16; const uint32_t expected = UINT32_C(0xC0FFEE42);
    HANDLE heap = GetProcessHeap(); unsigned char *block = HeapAlloc(heap, HEAP_ZERO_MEMORY, capacity + sizeof(expected));
    uint32_t observed;
    if (!block) return 1;
    memcpy(block + capacity, &expected, sizeof(expected));
    if (strcpy_s((char *)block, capacity, "safe") != 0) { HeapFree(heap, 0, block); return 1; }
    memcpy(&observed, block + capacity, sizeof(observed));
    printf("Sentinel %s: 0x%08X\n", observed == expected ? "unchanged" : "changed", observed);
    HeapFree(heap, 0, block); return observed == expected ? 0 : 1;
}
