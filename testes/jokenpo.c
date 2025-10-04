#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
    #define SleepMs(ms) Sleep(ms)
    #define Pause() system("pause")
    #define ClearScreen() system("cls")
#else 
    #include <unistd.h>
    #define SleepMs(ms) usleep((ms) * 1000)
    #define Pause() do { \
        printf("\nPress ENTER to continue!!\n"); \
        getchar(); \
    } while(0)
    #define ClearScreen() system("clear")
#endif

#ifdef _WIN32
HANDLE hConsole;
#endif

void printCor(const char *text, int InitColor, int EndColor, ...);
void type(const char *text, int ms);
void CleanIn(void);
void Line(void);

int main() {
    #ifdef _WIN32
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

    const char *game[] = {"Rock", "Paper", "Scissors"};
    int op, Cop;
    srand(time(NULL));

    do {
        #ifdef _WIN32
            printf("Running on Windows!!\n");
        #else
            printf("Running on Linux!!\n");
        #endif

        printf("\nYour options:\n");
        printCor("[0] Rock\n", 2, 4);      // Green to Red 
        printCor("[1] Paper\n", 4, 11);    // Red to Cyan
        printCor("[2] Scissors\n", 11, 7); // Cyan to White
        printf("\nChoose an option: ");
        scanf("%d", &op);
        CleanIn();

        if (!(op >= 0 && op <= 2)) {
            printCor("\nInvalid option!!\n", 12, 7); // Light red to White
            Pause();
            ClearScreen();
        }

    } while (op < 0 || op > 2);

    printf("\nRock\n");
    SleepMs(550);
    printf("Paper\n");
    SleepMs(550);
    printf("Scissors!!\n");

    Line();

    Cop = rand() % 3;

    printf("PLAYER chose: ");
    printCor("%s\n", 10, 7, game[op]); // Light Green to White

    printf("COMPUTER chose: ");
    printCor("%s\n", 4, 7, game[Cop]); // Red to White

    Line();

    if (Cop == op) {
        printCor("\nDraw!!\n", 6, 7); // Yellow to White
    } else if ( (Cop == 0 && op == 2) || (Cop == 1 && op == 0) || (Cop == 2 && op == 1) ) {
        printCor("\nComputer Wins!!\n", 4, 7); // Red to White
    } else {
        printCor("\nPlayer Wins!!\n", 2, 7); // Green to White
    }

    return 0;
}

// Função printCor adaptada para Windows e Linux
void printCor(const char *text, int InitColor, int EndColor, ...) {
    va_list args;
    va_start(args, EndColor);

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, InitColor);
    vprintf(text, args);
    SetConsoleTextAttribute(hConsole, EndColor);
#else
    // Mapeamento simples para cores ANSI (Linux/Unix)
    // Mapear as cores Windows para códigos ANSI aproximados:
    // 2=Green, 4=Red, 7=White, 10=Light Green, 11=Cyan, 12=Light Red, 6=Yellow

    // Função simples para converter InitColor para ANSI escape
const char* ansi_colors[] = {
        "\033[0m",    // 0 = reset
        "\033[30m",   // 1 = preto
        "\033[32m",   // 2 = verde
        "\033[34m",   // 3 = azul
        "\033[31m",   // 4 = vermelho
        "\033[35m",   // 5 = magenta
        "\033[33m",   // 6 = amarelo
        "\033[37m",   // 7 = branco
        "\033[90m",   // 8 = cinza escuro
        "\033[92m",   // 9 = verde claro
        "\033[92m",   // 10= verde claro
        "\033[96m",   // 11= ciano claro
        "\033[91m",   // 12= vermelho claro
    };

    if (InitColor >=0 && InitColor <= 12)
        printf("%s", ansi_colors[InitColor]);
    else
        printf("\033[0m"); // reset

    vprintf(text, args);
    printf("\033[0m"); // reset para cor padrão no final
#endif

    va_end(args);
}

void type(const char *text, int ms) {
    for(int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        SleepMs(ms);
    }
}

void CleanIn(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Line(void) {
    printf("\n--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--\n");
}