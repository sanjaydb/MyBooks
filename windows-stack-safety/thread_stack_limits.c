#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

int main(void) {
    ULONG_PTR low, high;
    GetCurrentThreadStackLimits(&low, &high);
    printf("Current thread stack range: 0x%p - 0x%p\n", (void *)low, (void *)high);
    printf("Reserved stack span: %llu bytes\n", (unsigned long long)(high - low));
    return 0;
}
