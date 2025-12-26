#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 0x400

#ifdef _WIN32
    #include <windows.h>
    #define clear() system("cls")
#else
    #include <unistd.h>
    #define clear() system("clear")
#endif

void charRm(char *str, int targ);

int main(void) {
    srand(time(NULL));
    char buffer[MAX_CHAR];
    int digits, lastnum;
    
    int firstTime = 1;
    
    while (1) {
        while (1) {
            printf("Enter the digit count: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            charRm(buffer, ' ');

            if (strcmp(buffer, "exit") == 0) {
                return 0;
            } else if (strcmp(buffer, "cls") == 0 || strcmp(buffer, "cls") == 0) {
                clear();
                continue;
            }

            int isalldigit = 1;
            size_t i = (buffer[0] == '-') ? 1 : 0;
            
            for (; buffer[i]; i++) {
                if (!isdigit(buffer[i]))
                    isalldigit = 0;
            }

            if (!isalldigit) {
                puts("Error: invalid data type!\n");
                continue;
            }

            sscanf(buffer, "%d", &digits);

            if (digits < 1 || digits > MAX_CHAR) {
                printf("Error: must be > 1 and < %d\n\n", MAX_CHAR);
                continue;
            }

            break;
        }
            char *str = malloc((size_t)digits + 1);
        
            if (!str) {
                puts("Error: memory allocation error!");
                return 1;
            }
        
            str[digits] = '\0';
        
            for (size_t i = 0; i < (size_t)digits; i++) {
                int r;
                do {
                    r = rand();
                } while (r >= RAND_MAX - (RAND_MAX % 10));

                str[i] = '0' + (r % 10);
            }
            
            int num = atoi(str);

            if (!firstTime)
                printf("Difference compared to the last number: %d\n\n", num - lastnum);

            printf("Number: '%d'\n\n", num);

            lastnum = num;
            firstTime = 0;
    }    

    return 0;
}

void charRm(char *str, int targ) {
    size_t  i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] != (char)targ) {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}