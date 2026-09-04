#include <stdio.h>

static int read_value(const int *values, size_t count, size_t index, int *result) {
    if (!values || !result || index >= count) return 0;
    *result = values[index];
    return 1;
}

int main(void) {
    const int values[] = {10, 20, 30, 40};
    int result;
    if (read_value(values, sizeof(values) / sizeof(values[0]), 2, &result))
        printf("values[2] = %d\n", result);
    if (!read_value(values, sizeof(values) / sizeof(values[0]), 10, &result))
        printf("Out-of-range index 10 was rejected.\n");
    return 0;
}
