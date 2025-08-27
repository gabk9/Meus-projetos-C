#include <stdio.h>

int main() {
    int a = 10, b = 20, result;

    __asm__ (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "orl %%ebx, %%eax;"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("%d OR %d = %d\n", a, b, result);

    __asm__ (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "xorl %%ebx, %%eax;"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("%d XOR %d = %d", a, b, result);

    return 0;
}