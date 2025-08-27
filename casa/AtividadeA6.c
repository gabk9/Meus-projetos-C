#include <stdio.h>

int main() {
    int a, result1, result2;
    a = 50;

    __asm__ (
        "movl %2, %%eax;"                   // eax = a
        "decl %%eax;"                       // eax = eax - 1
        "movl %%eax, %0;"                   // result1 = eax

        "movl %2, %%ebx;"                   // ebx = a
        "incl %%ebx;"                       // ebx = ebx + 1
        "movl %%ebx, %1;"                   // result2 = ebx
        : "=r" (result1), "=r" (result2)    // %0 = result1 | %1 = result2
        : "r" (a)                           // %2 = a
        : "%eax", "%ebx"                    // Clobber
    );

    printf("%d - 1 = %d\n%d + 1 = %d", a, result1, a, result2);

    return 0;
}