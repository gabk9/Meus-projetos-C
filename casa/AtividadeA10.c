#include <stdio.h>

int main() {
    int a = 10, b = 20, result;

    __asm__ (
        "xchg %0, %1;"
        : "+r" (a), "+r" (b)
    );

    printf("a = %d\nb = %d", a, b);

    return 0;
}