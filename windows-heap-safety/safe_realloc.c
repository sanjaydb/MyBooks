#include <windows.h>
#include <stdio.h>

int main(void) {
    HANDLE heap = GetProcessHeap(); size_t oldCount = 4, newCount = 8;
    int *values = HeapAlloc(heap, HEAP_ZERO_MEMORY, oldCount * sizeof(*values)); int *resized;
    if (!values) return 1;
    for (size_t i = 0; i < oldCount; ++i) values[i] = (int)(i + 1);
    resized = HeapReAlloc(heap, HEAP_ZERO_MEMORY, values, newCount * sizeof(*values));
    if (!resized) { HeapFree(heap, 0, values); return 1; }
    values = resized; printf("Resized safely from %zu to %zu elements.\n", oldCount, newCount);
    HeapFree(heap, 0, values); return 0;
}
