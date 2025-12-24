#include <stdio.h>

int main() {
    float a = 2.5, b = 3.7, result;

    asm volatile (
        "movss %1, %%xmm0;"
        "movss %2, %%xmm1;"
        "divss %%xmm1, %%xmm0;"
        "movss %%xmm0, %0;"
        : "=m"(result)
        : "m"(a), "m"(b)
        : "%xmm0", "%xmm1"
    );

    printf("%.2f / %.2f = %.2f\n", a, b, result);

    return 0;
}