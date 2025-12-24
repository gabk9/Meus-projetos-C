#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char str[sizeof(int) * 2];
    int n1, n2, result;

    printf("Enter the first integer: ");
    scanf("%d", &n1);
    
    printf("Enter the second integer: ");
    scanf("%d", &n2);

    snprintf(str, sizeof(str), "%d%d", n1, n2);

    result = atoi(str);

    printf("\n\n%d + %d = \'%d\'\n", n1, n2, result);

    return 0;
}