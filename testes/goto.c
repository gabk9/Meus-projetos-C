#include <stdio.h>

int main(int argc, char **argv) {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    printf("\n");
    int eax = n;

loop:
    printf("%d\n", eax);
    eax--;
    
    if (eax > 0) goto loop;

    return 0;
}