#include <stdio.h>

int main() {
    int a = 10, b = 6, c = 6, result;

    __asm__ (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "movl %3, %%ecx;"
        "addl %%ebx, %%eax;"
        "movl %%eax, %0;"
        "addl %%ecx, %%eax;"
        "movl %%eax, %0;"
        : "=r" (result)
        : "r" (a), "r" (b), "r" (c)
        : "%eax", "%ebx", "ecx"
    );

    printf("%d + %d + %d = %d", a, b, c, result);

    return 0;
}