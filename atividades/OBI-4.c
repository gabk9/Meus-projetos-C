#include <stdio.h>

int main(void) {
    int odd_max = 0, even_sum = 0, count = 0, has_odd = 0;


    while (1) {
        int num;
        scanf("%d", &num);
        
        if (num == 0)
            break;

        count++;
        
        if (!(num & 1)) {
            even_sum += num;
        } else {
            if (!has_odd || num > odd_max) {
                odd_max = num;
                has_odd = 1;
            }
        }
    }

    printf("%d\n%d\n%d\n\n", count, even_sum, odd_max);

    return 0;
}