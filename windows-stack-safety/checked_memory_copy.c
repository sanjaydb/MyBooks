#include <stdio.h>
#include <string.h>

static int copy_bytes(unsigned char *destination, size_t capacity,
                      const unsigned char *source, size_t count) {
    if (!destination || !source || count > capacity) return 0;
    memcpy(destination, source, count);
    return 1;
}

int main(void) {
    const unsigned char source[] = {10, 20, 30, 40};
    unsigned char destination[4] = {0};
    if (!copy_bytes(destination, sizeof(destination), source, sizeof(source))) return 1;
    printf("Copied bytes: %u %u %u %u\n", destination[0], destination[1], destination[2], destination[3]);
    return 0;
}
