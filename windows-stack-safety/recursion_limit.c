#include <stdio.h>

static unsigned int visit(unsigned int current, unsigned int maximum) {
    volatile unsigned char small_frame[32] = {0};
    small_frame[0] = (unsigned char)current;
    if (current >= maximum) return current + small_frame[0] - current;
    return visit(current + 1, maximum);
}

int main(void) {
    const unsigned int safeLimit = 100;
    printf("Stopped recursion safely at depth %u.\n", visit(0, safeLimit));
    return 0;
}
