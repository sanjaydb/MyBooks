#include <windows.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct { size_t length; unsigned char data[1]; } MESSAGE;
int main(void) {
    const char text[] = "bounded message"; size_t length = sizeof(text);
    size_t header = offsetof(MESSAGE, data), total; HANDLE heap = GetProcessHeap(); MESSAGE *message;
    if (length > SIZE_MAX - header) return 1;
    total = header + length; message = HeapAlloc(heap, 0, total); if (!message) return 1;
    message->length = length; memcpy(message->data, text, length);
    printf("Stored %zu bytes in a correctly sized allocation: %s\n", message->length, message->data);
    HeapFree(heap, 0, message); return 0;
}
