#include <stdio.h>

int main() {
    int a = 10, result;

    asm volatile (
        "negl %%eax;"
        "movl %%eax, %0;"
        : "=r"(result)
        : "r"(a)
    );

    printf("%d in inverted form: %d\n", a, result);

    return 0;
}