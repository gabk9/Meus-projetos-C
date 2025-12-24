#include <stdio.h>

int main() {
    int a = 4, resultL, resultR;

    asm volatile (
        "movl %2, %%eax;"
        "shl $2, %%eax;"
        "movl %%eax, %0;"
        "movl %2, %%eax;"
        "shr $2, %%eax;"
        "movl %%eax, %1;"
        : "=r"(resultL), "=r"(resultR)
        : "r"(a)
        : "%eax"
    );

    printf("%d << 2 = %d\n%d >> 2 = %d\n", a, resultL, a, resultR);

    return 0;
}