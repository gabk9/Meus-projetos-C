#include <stdio.h>

int main() {
    int a = 4, b = 5, c = 6;
    int quotient, remainder;

    asm volatile ( 
        "movl %2, %%eax;"
        "addl %3, %%eax;"
        "addl %4, %%eax;"
        "movl $3 , %%ebx;"
        "cltd;"
        "idivl %%ebx;" 
        "movl %%eax, %0;"
        "movl %%edx, %1;"
        : "=r"(quotient), "=r"(remainder)
        : "r"(a), "r"(b), "r"(c)
        : "%eax", "%ebx", "%edx"
    );

    printf("\nArithmetic mean: %d\nWith remainder: %d\n", quotient, remainder);

    return 0;
}