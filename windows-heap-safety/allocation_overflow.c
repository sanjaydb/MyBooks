#include <windows.h>
#include <stdio.h>
#include <stdint.h>

static int checked_multiply(size_t count, size_t elementSize, size_t *total) {
    if (!total || (elementSize != 0 && count > SIZE_MAX / elementSize)) return 0;
    *total = count * elementSize; return 1;
}
int main(void) {
    size_t count = 100, bytes; HANDLE heap = GetProcessHeap(); int *values;
    if (!checked_multiply(count, sizeof(*values), &bytes)) return 1;
    values = HeapAlloc(heap, HEAP_ZERO_MEMORY, bytes); if (!values) return 1;
    values[99] = 42; printf("Allocated %zu bytes; final value is %d.\n", bytes, values[99]);
    HeapFree(heap, 0, values);
    if (!checked_multiply(SIZE_MAX, 2, &bytes)) printf("Overflowing allocation size was rejected.\n");
    return 0;
}
