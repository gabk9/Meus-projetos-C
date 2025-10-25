#include <stdio.h>

int main() {
    int a, result;
    const int divisor = 2;

    printf("Type-in a number: ");
    scanf("%d", &a);

    asm volatile (
        "testl $1, %[num];" 
        "setne %b[result];"
        : [result] "=r" (result)
        : [num] "r" (a)
    );

    printf("\nThat's an %s number\n", result ? "Odd" : "Even");

    return 0;
}