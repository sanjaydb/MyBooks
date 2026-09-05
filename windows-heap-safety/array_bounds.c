#include <windows.h>
#include <stdio.h>

static int read_element(const int *values, size_t count, size_t index, int *result) {
    if (!values || !result || index >= count) return 0;
    *result = values[index]; return 1;
}
int main(void) {
    HANDLE heap = GetProcessHeap(); const size_t count = 4; int result;
    int *values = HeapAlloc(heap, 0, count * sizeof(*values)); if (!values) return 1;
    for (size_t i = 0; i < count; ++i) values[i] = (int)((i + 1) * 10);
    if (read_element(values, count, 2, &result)) printf("values[2] = %d\n", result);
    if (!read_element(values, count, 9, &result)) printf("Out-of-range index 9 was rejected.\n");
    HeapFree(heap, 0, values); return 0;
}
