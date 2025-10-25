#include <stdio.h>

int main() {
    const float qtd = 3.0f;
    float a = 4.0f, b = 5.5f, c = 6.0f;
    float result;

    asm volatile (
        "movss %1, %%xmm0;"
        "addss %2, %%xmm0;"
        "addss %3, %%xmm0;"
        "divss %4, %%xmm0;"
        "movss %%xmm0, %0;"
        : "=m"(result)
        : "m"(a), "m"(b), "m"(c), "m"(qtd)
        : "%xmm0"
    );

    printf("\nArithmetic mean: %.2f\n", result);

    return 0;
}