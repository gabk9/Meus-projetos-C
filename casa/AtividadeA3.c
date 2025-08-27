#include <stdio.h>

int main() {
    int a, b, result;
    a = 5, b = 5;

    __asm__ (
        "imull %%ebx, %%eax;"
        : "=a" (result)
        : "a" (a), "b" (b)
    );

    printf("Result of %d x %d = %d", a, b, result);

    return 0;
}