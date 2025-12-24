#include <stdio.h>

int main() {
    float a = 1.5f, b = 2.5f, c = 3.0f, result;

    asm volatile (
        "movss %1, %%xmm0;"
        "addss %2, %%xmm0;"
        "mulss %3, %%xmm0;"
        "movss %%xmm0, %0;"
        : "=m"(result)
        : "m"(a), "m"(b), "m"(c)
        : "%xmm0"
    );

    printf("(%.2f + %.2f) x %.2f = %.2f\n", a, b, c, result);

    return 0;
}