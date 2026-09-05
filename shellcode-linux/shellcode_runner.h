#ifndef SHELLCODE_RUNNER_H
#define SHELLCODE_RUNNER_H
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>

static void *prepare_shellcode(const unsigned char *bytes, size_t size) {
    void *memory = mmap(NULL, size, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) return NULL;
    memcpy(memory, bytes, size);
    if (mprotect(memory, size, PROT_READ | PROT_EXEC) != 0) {
        munmap(memory, size);
        return NULL;
    }
    return memory;
}

static void release_shellcode(void *memory, size_t size) {
    if (memory) munmap(memory, size);
}
#endif
