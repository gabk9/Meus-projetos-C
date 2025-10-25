#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
    #define SleepMS(ms) Sleep(ms)
    #define cls() system("cls")
    #define pause() system("pause")
    HANDLE hConsole;
#else
    #include <unistd.h>
    #define SleepMS(ms) usleep((ms) * 1000)
    #define cls() system("clear")
    #define pause() do { \
        printf("Pressione enter para continuar..."); \
        getchar(); \
    } while(0)
#endif

#define MAXPASSWORD 9999 // Colocado aqui para uma alteração mais fácil
#define MINPASSWORD 1 // Colocado aqui para uma alteração mais fácil (melhor usar 0 ou 1, o tamanho entre o máximo e o mínimo nunca muda)

void setCor(int cor);
void printCor(const char *texto, int cor, int corF, ...);
void type(const char *texto, int ms);
void Load(int ms, int Pcolor, int LoadColor);
void CleanIn();
void perguntas();
void gabarito();
char respostasUsuario[6] = {0};
int senha = 0;
int gabaritoLiberado = 0;

int main() {
    int pass, op;
    char buffer[20];
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));
    senha = (rand() % MAXPASSWORD) + MINPASSWORD; 

#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    do {
        printCor("\n=====ATIVIDADES=====\n", 2, 1); // Verde para Azul
        type("[1] Começar\n[2] Gabarito\n[3] Sair", 30);
        printCor("\nEscolha uma opção: ", 7, 1); // Branco para Azul
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &op) != 1) { // Lê o que vc digitou, guarda em um erray com o "fgets" e depois é analisado para ver se está de acordo com o tipo de formato
            printCor("\n\aValor inválido!!\n", 12, 7); // Vermelho Claro para Branco
            pause();
            cls();
            continue;
        } else {
            if(op >= 1 && op <= 3) {
                switch(op) {    
                    case 1: perguntas(); break;
                    case 2:
                        printCor("Digite a senha: ", 7, 2); // Branco para Verde
                        if (scanf("%d", &pass) == 1) { // Verifica se é um número inteiro
                            CleanIn();
                            if (pass == senha) {
                                printCor("\nAcesso Permitido!!\n", 10, 7);  // Verde Claro para Branco
                                if(gabaritoLiberado == 0) {
                                    Load(25, 7, 5); // Branco para Roxo
                                }
                                cls();
                                gabarito();
                            } else {
                                printCor("\nAcesso negado!!\n", 12, 7); // Vermelho Claro para Branco
                                pause();
                                cls();
                            }
                        } else {
                            CleanIn();
                            printCor("\n\aA senha é composta apenas por números\n", 12, 7);
                            pause();
                            cls();
                        }
                        break;
                    case 3: printCor("\nSaindo...\n", 4, 7); break; // Vermelho para Branco
                }
        
            } else {
                printCor("\n\aValor inválido!!\n", 12, 7); // Vermelho claro para Branco
                pause();
                cls();
            }
        }

    } while(op != 3);

    return 0;
}

void type(const char *texto, int ms) {
    for(int i = 0; texto[i] != '\0'; i++) {
        putchar(texto[i]);
        fflush(stdout);
        SleepMS(ms);
    }
}

void perguntas() {  
    char r;
    int i = 0;

    const char *perguntas[] = {
        "[1] Qual tipo armazena valores com ponto flutuante e maior precisão?\n\n",
        "[2] Qual tipo de variável serve para ler caracteres alfanuméricos?\n\n",
        "[3] Qual desses NÃO é um tipo de variável da linguagem C?\n\n",
        "[4] Qual tipo de variável armazena números inteiros positivos e negativos?\n\n",
        "[5] Qual tipo de variável é recomendado para armazenar textos (sequências de caracteres) em C?\n\n",
        "[6] Qual tipo de variável em C é usado para armazenar números inteiros muito grandes?\n\n"
    };

    const char *opcoes[] = {
        "A) int\nB) char\nC) double\nD) float\nE) size_t\n\n",
        "A) BigInt\nB) char\nC) double\nD) short\nE) bool\n\n",
        "A) long\nB) short\nC) float\nD) string\nE) double\n\n",
        "A) unsigned int\nB) long\nC) int\nD) float\nE) bool\n\n",
        "A) char[]\nB) int\nC) double\nD) bool\nE) char\n\n",
        "A) short\nB) int\nC) long long\nD) float\nE) bool\n\n"
    };

    const char respostasCorretas[] = {'c', 'b', 'd', 'c', 'a', 'c'};

    while (1) {
        cls();

        for (i = 0; i < 6; i++) {
            setCor(10); // Verde claro
            type(perguntas[i], 30);
            printCor(opcoes[i], 6, 7); // Amarelo para Branco

            while (1) {
                printf("Qual alternativa julga correta? ");
                setCor(4); // Vermelho
                scanf("%c", &r);
                setCor(7); // Branco
                CleanIn();

                r = tolower(r);

                if (r >= 'a' && r <= 'e') {
                    if (r == respostasCorretas[i]) {
                        printCor("\nResposta Correta!\n", 10, 7); // Verde claro para Branco
                        pause();
                        cls();
                        break;
                    } else {
                        printCor("\n\aResposta incorreta! Voltando ao início.\n", 12, 7); // Vermelho claro para Branco 
                        pause();
                        cls();
                        return;
                    }
                } else {
                    printCor("\n\aResposta inválida! Digite apenas letras e que sejam de A até E.\n", 12, 7); // Vermelho claro para Branco
                    pause();
                    cls();
                    setCor(10); // Verde claro
                    type(perguntas[i], 30);
                    printCor(opcoes[i], 6, 7); // Amarelo para Branco
                }
            }
        }

        printCor("Parabéns! Você respondeu todas corretamente!\n", 10, 7); // Verde claro para Branco
        printf("A senha gerada é: ");
        printCor("%d\n", 2, 7, senha); // Verde para Branco
        pause();
        cls();
        break;
    }
}

void gabarito() {
    gabaritoLiberado = 1;
    const char *perguntas[] = {
        "[1] Qual tipo armazena valores com ponto flutuante e maior precisão?\n\n",
        "[2] Qual tipo de variável serve para ler caracteres alfanuméricos?\n\n",
        "[3] Qual desses NÃO é um tipo de variável da linguagem C?\n\n",
        "[4] Qual tipo de variável armazena números inteiros positivos e negativos?\n\n",
        "[5] Qual tipo de variável é recomendado para armazenar textos (sequências de caracteres) em C?\n\n",
        "[6] Qual tipo de variável em C é usado para armazenar números inteiros muito grandes?\n\n"
    };

    const char *opcoes[] = {
        "A) int\nB) char\nC) double\nD) float\nE) size_t\n",
        "A) BigInt\nB) char\nC) double\nD) short\nE) bool\n",
        "A) long\nB) short\nC) float\nD) string\nE) double\n",
        "A) unsigned int\nB) long\nC) int\nD) float\nE) bool\n",
        "A) char[]\nB) int\nC) double\nD) bool\nE) char\n",
        "A) short\nB) int\nC) long long\nD) float\nE) bool\n"
    };

    const char respostasCorretas[] = {'c', 'b', 'd', 'c', 'a', 'c'};

    for (int i = 0; i < 6; i++) {
        cls();
        setCor(11); // Aqua claro
        printf("%s", perguntas[i]);

        const char *op = opcoes[i]; // É usado ponteiro porque "opcoes" também é um
        char letra = 'a';

        while (*op) {
            if (letra == tolower(respostasCorretas[i])) {
                setCor(10); // Verde claro
            } else {
                setCor(6); // Amarelo
            }

            while (*op && *op != '\n') {
                putchar(*op++);
            }
            putchar('\n');
            if (*op == '\n') op++;

            letra++;
        }
        printCor("\n\nCorretas\n", 160, 96); // Fundo verde claro com texto preto para fundo Amarelo texto preto
        printf("Incorretas\n\n");
        
        setCor(7); // Branco
        pause();
    }
    cls();
}

void setCor(int cor) {
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, cor);
#else
    switch(cor) {
        case 2: printf("\033[32m"); break; // Verde
        case 4: printf("\033[31m"); break; // Vermelho
        case 6: printf("\033[33m"); break; // Amarelo
        case 7: printf("\033[37m"); break; // Branco
        case 10: printf("\033[92m"); break; // Verde claro
        case 11: printf("\033[96m"); break; // Ciano claro
        case 12: printf("\033[91m"); break; // Vermelho claro
        default: printf("\033[0m"); break; // Reset
    }
#endif
} 
void printCor(const char *texto, int cor, int corF, ...) {
    setCor(cor);

    va_list args;
    va_start(args, corF);
    vprintf(texto, args);
    va_end(args);

    setCor(corF);
}

void CleanIn(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Load(int ms, int Pcolor, int LoadColor) {
    setCor(Pcolor);
    printf("\nCarregando...\n");
    setCor(LoadColor);
    for(int i = 0; i <= 100; i++) {
        printf("\r[%3d%%]", i);
        fflush(stdout);
        SleepMS(ms);
    }
    setCor(7);
}