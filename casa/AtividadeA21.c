#include <stdio.h>

int main() {
    int age, result;

    printf("Type-in your age: ");
    scanf("%d", &age);


    asm volatile (
        "movl %1, %%eax;"
        "cmp $18, %%eax;"
        "setge %%al;"       // if 18 >= age
        "movzbl %%al, %0;"
        : "=r"(result)
        : "r"(age)
        : "%eax"
    );

    const char *resultAge = (result) ? "Legal Age" : "Minor";

    printf("\n%s\n", resultAge);

    return 0;
}