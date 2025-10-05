#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 0x40

int input(char *buffer, size_t size, const char *fmt, void *out);

int main(void) {
    char *buffer = calloc(MAXCHAR, sizeof(char));
    char str[MAXCHAR];
    int num;
    float Fnum;

    printf("Enter a string: ");
    input(buffer, MAXCHAR, "%s", str);
    printf("You typed: %s\n", buffer);


    printf("\nEnter an integer: ");
    input(buffer, MAXCHAR, "%d", &num);
    printf("You typed : %d\n", num);
    
    printf("\nEnter a float: ");
    input(buffer, MAXCHAR, "%f", &Fnum);
    printf("You typed : %.2f\n", Fnum);

    return 0;
}

int input(char *buffer, size_t size, const char *fmt, void *out) {
    while (1) {
        if (!fgets(buffer, size, stdin)) {
            return 0;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(fmt, "%s") == 0) {
            strcpy(out, buffer);
            return 1;
        } 
        else if (sscanf(buffer, fmt, out) == 1) {
            return 1;
        } 
        else {
            printf("Invalid input, try again: ");
        }
    }
}