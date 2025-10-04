#include <stdio.h>

int main() {
    int a, b;
    int result;

    printf("type-in a number: ");
    scanf("%d", &a);

    printf("\nAnother one: ");
    scanf("%d", &b);
    
    __asm__ (
        "movl %1, %%eax;"
        "addl %2, %%eax;" 
        : "=a" (result) 
        : "r" (a), "r" (b)
    );
    
    printf("\nResultado de %d + %d: %d", a, b, result);

    return 0;
}