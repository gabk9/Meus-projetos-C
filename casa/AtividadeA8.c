#include <stdio.h>

int main() {
    int a = 10, b = 6, c = 6, result = 0;


    __asm__ (
        "addl %%ebx, %%eax;"            // eax = eax + ebx
        "addl %%ecx, %%eax;"            // eax = eax + ecx
        : "=a" (result)                 // output: em eax → result
        : "a" (a), "b" (b), "c" (c)     // fixed inputs: eax, ebx, ecx
    );


    printf("%d + %d + %d = %d", a, b, c, result);

    return 0;
}