#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define Clear() system("cls")
    #define Pause() system("pause")
    #define SleepMS(ms) Sleep(ms)
#elif defined(__linux__) || defined(__APPLE__) 
    #include <unistd.h>
    #define Clear() system("clear")
    #define Pause() do { \
        printf("\nPress ENTER to continue..."); \
        getchar(); \
    } while(0)
    #define SleepMS(ms) usleep((ms) * 1000)
#else 
    #error "Operational system not recognized, terminating program!!\n"
#endif


#define MAX_CHAR 100


void CleanIn();
void Addition(int a, int b);
void Division2(int a, int b);
void Subtraction(int a, int b);
void Division(float a, float b);
void Multiplication(int a, int b);


int main() {
    char *buff = calloc(MAX_CHAR, sizeof(char));
    int a, b, op;

    if(!buff) {
        printf("Error: Allocation error!!\n");
        return 1;
    }

    do {
        printf("======Calculator======\n");
        printf("[1] Multiplication\n[2] Division\n[3] Addition\n[4] Subtraction\n[0] Exit program\n");
        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL;
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        if(op) {
            printf("Type-in the 1st number: ");
            scanf("%d", &a);
            CleanIn();
    
            printf("Type-in the 2nd number: ");
            scanf("%d", &b);
            CleanIn();
        }

        switch(op) {
            case 1:
                Multiplication(a, b);
                break;
            case 2:
                Division(a, b);
                printf("\nOr\n");
                Division2(a, b);
                break;
            case 3:
                Addition(a, b);
                break;
            case 4:
                Subtraction(a, b);
                break;
            case 0:
                printf("\nTerminating program, bye!!\n");
                Pause();
                break;
            default:
                printf("\nError Operation not permitted!\n");
                Pause();
                Clear();
                continue;
        }

    } while(op != 0);

    return 0;
}

void Multiplication(int a, int b) {
    int result;
    asm volatile (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "imull %%ebx, %%eax;"
        "movl %%eax, %0;"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("\n%d x %d = %d\n", a, b, result);
    Pause(); 
    Clear();
}

// I used "m" bc SSE uses m (memory), not r (register)
void Division(float a, float b) { 
    float result;
    asm volatile (
        "movss %1, %%xmm0;"
        "movss %2, %%xmm1;"
        "divss %%xmm1, %%xmm0;"
        "movss %%xmm0, %0;"
        : "=m" (result)
        : "m" (a), "m" (b)
    );

    printf("\n%.2f / %.2f = %.2f\n", a, b, result);
}

void Division2(int a, int b) {
    int quotient, rest;
    asm volatile (
        "movl %2, %%eax;"
        "cltd;"
        "idivl %3;"
        "movl %%eax, %0;"
        "movl %%edx, %1;"
        : "=r"(quotient), "=r"(rest)
        : "r"(a), "r"(b)
        : "%eax", "%edx"
    );

    printf("\n%d / %d = %d with remainder %d\n", a, b, quotient, rest);
    Pause();
    Clear();
}

void Addition(int a, int b) {
    int result;
    asm volatile (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "addl %%ebx, %%eax;"
        "movl %%eax, %0;"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("\n%d + %d = %d\n", a, b, result);
    Pause();
    Clear();
}

void Subtraction(int a, int b) {
    int result;
    asm volatile (
        "movl %1, %%eax;"
        "movl %2, %%ebx;"
        "subl %%ebx, %%eax;"
        "movl %%eax, %0;"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("\n%d - %d = %d\n", a, b, result);
    Pause();
    Clear();
}

void CleanIn() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}