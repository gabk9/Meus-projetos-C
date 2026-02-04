#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX_CHAR 0x400

struct float_vector {
    float *data;
    int32_t length;
};

void charRm(char *str, uint8_t chr);
uint8_t is_valid_number(const char *str);
uint32_t count_index(const char *str, uint8_t targ);

int main(void) {
    char buff[MAX_CHAR];
    float houses_number = 0;
    struct float_vector houses_kWh = {.data = NULL,
                                        .length = 0
                                    };
    uint32_t surpasses_limit = 0;

    float limit = 0.0; 

    while (1) {
        printf("Enter a number: ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = '\0';
        charRm(buff, ' ');

        if (!*buff) {
            printf("Error: empty input\n\n");
            continue;
        }

        if (!is_valid_number(buff)) {
            printf("Error: invalid input type\n\n");
            continue;
        }

        houses_number = atof(buff);

        if (houses_number < 1 || houses_number > 1000) {
            printf("Error: the number of houses must be between 1 and 1000 (inclusive)\n\n");
            continue;
        }

        if (houses_number != (uint32_t)houses_number) {
            printf("Error: the number must be integer\n\n");
            continue;
        }

        houses_kWh.length = houses_number;
        houses_kWh.data = malloc(houses_number * sizeof(*houses_kWh.data));

        if (!houses_kWh.data) {
            printf("Error: memory allocation error\n\n");
            return 1;
        }

        for (uint32_t i = 0; i < houses_number;) {

            printf("\tEnter the consume of the house n%"PRIu32": ", i + 1);
            fgets(buff, sizeof(buff), stdin);
            buff[strcspn(buff, "\n")] = '\0';

            if (!*buff) {
                printf("\tError: empty input\n\n");
                continue;
            }

            if (!is_valid_number(buff)) {
                printf("\tError: invalid input type\n\n");
                continue;
            }

            float kWh = atof(buff);

            if (kWh < 0) {
                printf("\tError: the consume can not be negative\n\n");
                continue;
            }

            houses_kWh.data[i] = kWh;

            i++;
        }

        printf("\t\tEnter the consume limit: ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = '\0';

        if (!*buff) {
            printf("\t\tError: empty input\n\n");
            continue;
        }

        if (!is_valid_number(buff)) {
            printf("\t\tError: invalid input type\n\n");
            continue;
        }

        limit = atof(buff);

        break;
    }

    float max = *houses_kWh.data;
    float min = *houses_kWh.data;

    for (uint32_t i = 0; i < houses_kWh.length; i++) {
        if (houses_kWh.data[i] > limit)
            surpasses_limit++;

        if (max < houses_kWh.data[i])
            max = houses_kWh.data[i];

        if (min > houses_kWh.data[i])
            min = houses_kWh.data[i];
    }

    
            
    printf("\nHouses that are above the limit: %"PRIu32"\n", surpasses_limit);
    printf("Biggest consume: %g\n", max);
    printf("Smallest consume: %g\n", min);

    free(houses_kWh.data);

    return 0;
}

uint32_t count_index(const char *str, uint8_t targ) {
    uint32_t count = 0;
    for (size_t i = 0; str[i]; i++)
        if (str[i] == targ)
            count++;

    return count;
}

void charRm(char *str, uint8_t chr) {
    size_t i = 0, j = 0;
    
    while (str[i]) {
        
        if (str[i] != chr) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

uint8_t is_valid_number(const char *str) {

    if (count_index(str, '.') > 1)
        return 0;

    size_t j = (str[0] == '-') ? 1 : 0;

    for (j; str[j]; j++)
        if ((str[j] < '0' || str[j] > '9') && str[j] != '.')
            return 0;

    return 1;
}