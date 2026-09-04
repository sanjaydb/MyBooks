#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    HANDLE heap = GetProcessHeap(); char *copy; size_t length;
    if (argc != 2) { fprintf(stderr, "Usage: %s TEXT\n", argv[0]); return 2; }
    length = strlen(argv[1]);
    if (length > 4096) { fprintf(stderr, "Input is too long.\n"); return 1; }
    copy = HeapAlloc(heap, 0, length + 1); if (!copy) return 1;
    if (strcpy_s(copy, length + 1, argv[1]) != 0) { HeapFree(heap, 0, copy); return 1; }
    printf("Copied safely: %s\n", copy); HeapFree(heap, 0, copy); return 0;
}
