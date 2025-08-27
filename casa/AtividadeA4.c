#include <stdio.h>

int main() {
    int a, b, result;
    a = 10, b = 10; 

    // 10 in binary: 00001010
    // 100 in binary: 0110100

    __asm__ (
        "andl %%ebx, %%eax;"
        : "=a" (result) // result: 0000000 -> 0
        : "a" (a), "b" (b)
    );

    printf("Result of %d & %d = %d", a, b, result);

    return 0;
}