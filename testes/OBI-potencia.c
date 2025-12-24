#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 0x80

char main(void) {
    int qtd = 0;
    int num;
    double result = 0;
    char *buffer = calloc(MAXCHAR, sizeof(char));

    if (!buffer) {
        printf("Error: memory allocation error!\n");
        return 1;
    }
    
    while (1) {
        printf("Enter the amount of numbers that'll be used: ");
        fgets(buffer, MAXCHAR, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
    
        if (sscanf(buffer, "%d", &qtd) != 1) {
            printf("Error: invalid data type!\n");
            continue;
        }

        if (qtd < 1 || qtd > 10) {
            printf("Error: invalid amount!\n");
            continue;
        }

        for (int i = 0; i < qtd;) {
            printf("Enter a number: ");
            fgets(buffer, MAXCHAR, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            if (sscanf(buffer, "%d", &num) != 1) {
                printf("Error: invalid data type!\n");
                continue;
            }

            if (num < 10 || num > 9999) {
                printf("Error: invalid number!\n");
                continue;
            }

            snprintf(buffer, 4, "%d", num);

            int len = strlen(buffer);

            char *exponent = malloc(2);

            if (!exponent) {
                printf("Error: memory allocation error!\n");
                return 1;
            }

            exponent[0] = buffer[len - 1];
            exponent[1] = '\0';

            buffer[len-1] = '\0';

            result += pow(atof(buffer), atof(exponent));

            i++;
        }

        break;
    }

    printf("Final result: %g\n", result);

    return 0;
}