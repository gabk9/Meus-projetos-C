#include <stdio.h>

int get_digits_sum(int num);

int main(void) {
    int sum_res, num1, num2, count = 0;

    scanf("%d", &sum_res);

    scanf("%d", &num1);

    scanf("%d", &num2);

    for (int i = num1; i <= num2; i++)
        if (get_digits_sum(i) == sum_res)
            count++;

    printf("%d", count);

    return 0;
}

int get_digits_sum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}