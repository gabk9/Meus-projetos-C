#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define LINE "=========================="

#ifndef _WIN32
    #undef PRIu16
    #define PRIu16 "hu" 
#endif

int main(void) {

    uint16_t days_count = 0;
    uint16_t exceed_limit = 0;

    float limit = 0;

    scanf("%"PRIu16, &days_count);

    float *consume = malloc(days_count * sizeof(*consume));

    if (!consume)
        return 1;

    for (uint16_t i = 0; i < days_count; i++) 
        scanf("%f", &consume[i]);

    scanf("%f", &limit);

    float max_diff = consume[1] - consume[0];
    float min_diff = consume[1] - consume[0];

    for (uint16_t i = 1; i < days_count; i++) {
        float difference = consume[i] - consume[i-1];

        if (difference > limit)
            exceed_limit++;

        if (max_diff < difference)
            max_diff = difference;
            
        if (min_diff > difference)
            min_diff = difference;
    }

    puts("\n"LINE"\n");

    printf("%u\n%g\n%g\n\n", exceed_limit, max_diff, min_diff);

    free(consume);

    return 0;
}