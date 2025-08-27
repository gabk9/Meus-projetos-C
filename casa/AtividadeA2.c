#include <stdio.h>

int main() {
    int a, b, result;
    a = 100, b = 500;

    __asm__ (
        "subl %%ebx, %%eax;"
        : "=a" (result)
        : "a" (a), "b" (b)
    );

    printf("Result of %d - %d = %d", a, b, result);

    return 0;
}