#define _POSIX_C_SOURCE 199309L
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

int main(int argc, char **argv) {
#ifdef _WIN32
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    srand((unsigned)counter.QuadPart);
#else
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    srand((unsigned)(ts.tv_nsec ^ ts.tv_sec));
#endif
    
    char buffer[MAX_CHAR];
    long long num, lastnum;
    long long digits;

    int firstTime = 1;

    while (1) {
        while (1) {
            if (argc <= 1) {
                printf("Enter the digit count: ");
                fgets(buffer, sizeof(buffer), stdin);
            }

            if (argc > 1)
                strcpy(buffer, argv[1]);
            
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
                if (argc <= 1) {
                    puts("Error: invalid data type\n");
                } else {
                    puts("Error: invalid data type");
                    return 0;
                }

                continue;
            }

            digits = atoll(buffer);

            if (digits < 1 || digits > 18) {
                if (argc <= 1) {
                    puts("Error: must be > 1 and < 19\n");
                } else {
                    puts("Error: must be > 1 and < 19");
                    return 0;
                }


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
            
            long long num = atoll(str);

            if (!firstTime) {
                long long diff = (num > lastnum) ? num - lastnum : lastnum - num; 
                printf("Difference compared to the last number: %lld\n\n", diff);
            }

            if (argc <= 1) 
                printf("Number: '%lld'\n\n", num);
            else 
                printf("Number: '%lld'\n", num);


            lastnum = num;
            firstTime = 0;
            free(str);

            if (argc > 1)
                break;
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