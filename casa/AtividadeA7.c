#include <stdio.h>

#define A 50

int main() {
    int result1, result2;

    __asm__ (
        "movl %2, %%eax;"
        "decl %%eax;"
        "movl %%eax, %0;"
        "movl %2, %%ebx;"
        "incl %%ebx;"
        "movl %%ebx, %1;"
        : "=r" (result1), "=r" (result2)
        : "r" (A)
        : "%eax", "%ebx" 
    );

    printf("%d - 1 = %d\n%d + 1 = %d\n", A, result1, A, result2);

    return 0;
}