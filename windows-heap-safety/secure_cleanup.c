#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    HANDLE heap = GetProcessHeap(); const char sample[] = "temporary demonstration value";
    size_t size = sizeof(sample); char *buffer = HeapAlloc(heap, 0, size);
    if (!buffer) return 1;
    memcpy(buffer, sample, size); printf("Temporary value length: %zu\n", strlen(buffer));
    SecureZeroMemory(buffer, size); HeapFree(heap, 0, buffer);
    printf("Buffer cleared before release.\n"); return 0;
}
