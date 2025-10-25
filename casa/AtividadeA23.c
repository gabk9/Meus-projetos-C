#include <stdio.h>

int main() {
    int a = 0xF0F0, mask = 0x0FF0, result;

    asm volatile (
        "movl %1, %%eax;"
        "andl %2, %%eax;"
        "movl %%eax, %0;"
        : "=r"(result)
        : "r"(a), "r"(mask)
    );

    printf("a     = 0x%X\n", a);
    printf("mask  = 0x%X\n", mask);
    printf("result= 0x%X\n", result);

    return 0;
}