#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LINE "=========================="

int main(void) {

    uint32_t num = 0;
    uint32_t outside_limit = 0;

    float *consume = NULL;
    float limit = 0;

    scanf("%u", &num);

    consume = malloc(num * sizeof(*consume));

    if (!consume)
        return 1;

    for (uint32_t i = 0; i < num; i++)
        scanf("%f", &consume[i]);

    scanf("%f", &limit);

    puts("\n"LINE"\n");

    float min = *consume;
    float max = *consume;

    for (uint32_t i = 0; i < num; i++) {

        if (consume[i] > limit)
            outside_limit++;

        if (min > consume[i])
            min = consume[i];
        
        if (max < consume[i])
            max = consume[i];
    }

    printf("%d\n%g\n%g\n\n", outside_limit, max, min);

    free(consume);

    return 0;
}