#include <stdio.h>
#include <string.h>

static int copy_text(char *destination, size_t capacity, const char *source) {
    size_t length = strlen(source);
    if (length + 1 > capacity) return 0;
    memcpy(destination, source, length + 1);
    return 1;
}

int main(void) {
    char buffer[8];
    if (!copy_text(buffer, sizeof(buffer), "1234567")) return 1;
    printf("Seven characters plus terminator fit: %s\n", buffer);
    if (!copy_text(buffer, sizeof(buffer), "12345678"))
        printf("Eight characters were rejected because the terminator also needs space.\n");
    return 0;
}
