#include <stdio.h>

#define A 15
#define B 15

int main() {
    int result;

    __asm__ (
        "movl %1, %%eax;"
        "addl %2, %%eax;"
        : "=a" (result)
        : "r" (A), "r" (B)
    );

    printf("Result of %d + %d = %d", A, B, result);

    return 0;
}