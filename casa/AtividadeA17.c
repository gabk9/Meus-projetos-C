#include <stdio.h>

int main() {
    int sum = 0, i = 0;

    asm volatile (
        "movl $0, %%eax;"
        "movl $10, %%ecx;"
        "loop_start:"
        "incl %%eax;"
        "loop loop_start;"
        "movl %%eax, %0;"
        : "=r"(sum)
        :
        : "%eax", "%ecx"
    );

    printf("Counter: %d\nAccumulator: %d", i, sum);
}