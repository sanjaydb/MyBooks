#ifndef SHELLCODE_RUNNER_H
#define SHELLCODE_RUNNER_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stddef.h>
#include <string.h>

static void *prepare_shellcode(const unsigned char *bytes, size_t size) {
    DWORD oldProtection;
    void *memory = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!memory) return NULL;
    memcpy(memory, bytes, size);
    if (!VirtualProtect(memory, size, PAGE_EXECUTE_READ, &oldProtection)) {
        VirtualFree(memory, 0, MEM_RELEASE);
        return NULL;
    }
    FlushInstructionCache(GetCurrentProcess(), memory, size);
    return memory;
}

static void release_shellcode(void *memory) {
    if (memory) VirtualFree(memory, 0, MEM_RELEASE);
}
#endif
