#include <stdio.h>

int main() {
    int a = 2, b = 3, c = 5, result;

    asm volatile (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "movl %3, %%ecx;"
        "imull %%ebx, %%eax;"
        "addl %%ecx, %%eax;"
        "movl %%eax, %0;"
        : "=r"(result)
        : "r"(a), "r"(b), "r"(c)
        : "%eax", "%ebx", "%ecx"
    );

    printf("%d x %d + %d = %d", a, b, c, result);

    return 0;
}