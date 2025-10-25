#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool prime(int n);

int main(void) {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    char *cmp = (prime(num)) ? "is" : "isn't";
    printf("%d %s prime\n", num, cmp);

    return 0;
}

bool prime(int n) {
    if (n < 2) return false;
    
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    
    return true;
}