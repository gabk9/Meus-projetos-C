#include <stdio.h>

typedef enum {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
} days;

int main(void) {
    days week;

    printf("Type-in a number: ");
    scanf("%d", (int *)&week);

    week--;

    if (week < SUNDAY || week > SATURDAY) {
        printf("Invalid number!\n");
        goto leave;
    }
    
    char *result = (week == SATURDAY || week == SUNDAY) ? "Weekend" : "Weekday";

    printf("%s\n", result);

leave:
    return 0;
}