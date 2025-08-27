#include <stdio.h>

int main() {
    int a, b, result;
    a = 10, b = 20;

    __asm__ ( // Assembly inline
        "addl %%ebx, %%eax;" // eax = eax + ebx
        :"=a" (result)       // output: result = eax
        :"a" (a), "b" (b)    // input: a -> eax, b -> ebx
    );

    printf("Result of %d + %d = %d", a, b, result);

    return 0;
}