#include <stdio.h>
#include <string.h>

int isalldigit(char *str);
void charRm(char *str, int target);

int main(void) {
    char buff[0x400];
    int num;

    printf("Press zero to exit\n\n");

    while (1) {
        while (1) {
            printf("Enter a number: ");
            if (!fgets(buff, sizeof(buff), stdin)) {
                printf("Error: input error\n\n");
                continue;
            }
            buff[strcspn(buff, "\n")] = '\0';
    
            if (!isalldigit(buff)) {
                printf("Error: invalid data type\n\n");
                continue;
            }
    
            sscanf(buff, "%d", &num);
    
            break;
        }
    
        if (num == 0) {
            puts("Zero");
            break;
        }

        if (num & 1)
            puts("Odd\n");
        else
            puts("Even\n");
    }

    return 0;
}

void charRm(char *str, int target) {
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] != (char)target) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int isalldigit(char *str) {
    charRm(str, ' ');
    int i = (str[0] == '-') ? 1 : 0;
    for (i; str[i]; i++)
        if (str[i] < 0x30 || str[i] > 0x39)
            return 0;
    return 1;
}