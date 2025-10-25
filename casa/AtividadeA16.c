#include <stdio.h>

int main() {
    int a = 10, b = 7, result;

    asm volatile (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "cmp %%ebx, %%eax;"
        "setl %%al;"        // if a < b
        "movzbl %%al, %0;"
        : "=r"(result)
        : "r"(a), "r"(b)
        : "%eax", "%ebx"
    );

    const char *bin = (result) ? "True" : "False";

    printf("%d < %d = %s\n", a, b, bin);
    printf("or\n%d < %d = %d\n", a, b, result);

    return 0;
}