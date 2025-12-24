#include <stdio.h>

int main() {
    int a = 20, b = 3, quotient, rest;

    asm volatile (
        "movl %2, %%eax;"            // EAX = a (dividend)
        "cltd;"                      // sign-extend EAX into EDX:EAX (for signed division)
        "idivl %3;"                  // divide EDX:EAX by b (%3). ONLY WORKS WITH EAX AND EDX
                                     // result: EAX = quotient, EDX = remainder
        "movl %%eax, %0;"            // store EAX (quotient) into 'quotient'
        "movl %%edx, %1;"            // store EDX (remainder) into 'rest'
        : "=r"(quotient), "=r"(rest) // outputs
        : "r"(a), "r"(b)             // inputs
        : "%eax", "%edx"             // registers used (clobbered)
    );

    printf("%d / %d = %d with remainder %d\n", a, b, quotient, rest);

    return 0;
}
