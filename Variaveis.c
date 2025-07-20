#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>
#include <stdarg.h>

#define MAXPASSWORD 9999 // Colocado aqui para uma altera��o mais f�cil
#define MINPASSWORD 1 // Colocado aqui para uma altera��o mais f�cil (melhor usar 0 ou 1, o tamanho entre o m�ximo e o m�nimo nunca muda)

void setCor(int cor);
void printCor(const char *texto, int cor, int corF, ...);
void type(const char *texto, int ms);
void Load(int ms, int Pcolor, int LoadColor);
void CleanIn();
void perguntas();
void gabarito();
char respostasUsuario[6] = {0};
int senha = 0;
HANDLE hConsole;

int main() {
    int pass, op;
    char buffer[20];
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Portuguese_Brazil");
    srand(time(NULL));
    senha = (rand() % MAXPASSWORD) + MINPASSWORD; 

    do {
        printCor("\n=====ATIVIDADES=====\n", 2, 1); // Verde para Azul
        type("[1] Come�ar\n[2] Gabarito\n[3] Sair", 30);
        printCor("\nEscolha uma op��o: ", 7, 1); // Branco para Azul
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &op) != 1) { // L� o que vc digitou, guarda em um erray com o "fgets" e depois � analisado para ver se est� de acordo com o tipo de formato
            printCor("\n\aValor inv�lido!!\n", 12, 7); // Vermelho Claro para Branco
            system("pause");
            system("cls");
            continue;
        } else {
            if(op >= 1 && op <= 3) {
            switch(op) {    
                case 1: perguntas(); break;
                case 2:
                    printCor("Digite a senha: ", 7, 2); // Branco para Verde
                    if (scanf("%d", &pass) == 1) { // Verifica se � um n�mero inteiro
                        CleanIn();
                        if (pass == senha) {
                            printCor("\nAcesso Permitido!!\n", 10, 7);  // Verde Claro para Branco
                            Load(25, 7, 5); // Branco para Roxo
                            system("cls");
                            gabarito();
                        } else {
                            printCor("\nAcesso negado!!\n", 12, 7); // Vermelho Claro para Branco
                            system("pause");
                            system("cls");
                        }
                        } else {
                            CleanIn();
                            printCor("\n\aA senha � composta apenas por n�meros\n", 12, 7);
                            system("pause");
                            system("cls");
                        }
                        break;
                    case 3:
                        printCor("\nSaindo...\n", 4, 7); // Vermelho para Branco
                        break;
            }
        
        } else {
            printCor("\n\aValor inv�lido!!\n", 12, 7); // Vermelho claro para Branco
            system("pause");
            system("cls");
        }
        }

    } while(op != 3);

    return 0;
}

void type(const char *texto, int ms) {
    for(int i = 0; texto[i] != '\0'; i++) {
        putchar(texto[i]);
        fflush(stdout);
        Sleep(ms);
    }
}

void perguntas() {  
    char r;
    int i = 0;

    const char *perguntas[] = {
        "[1] Qual tipo armazena valores com ponto flutuante e maior precis�o?\n\n",
        "[2] Qual tipo de vari�vel serve para ler caracteres alfanum�ricos?\n\n",
        "[3] Qual desses N�O � um tipo de vari�vel da linguagem C?\n\n",
        "[4] Qual tipo de vari�vel armazena n�meros inteiros positivos e negativos?\n\n",
        "[5] Qual tipo de vari�vel � recomendado para armazenar textos (sequ�ncias de caracteres) em C?\n\n",
        "[6] Qual tipo de vari�vel em C � usado para armazenar n�meros inteiros muito grandes?\n\n"
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
        system("cls");

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
                        system("pause");
                        system("cls");
                        break;
                    } else {
                        printCor("\n\aResposta incorreta! Voltando ao in�cio.\n", 12, 7); // Vermelho claro para Branco 
                        system("pause");
                        system("cls");
                        return;
                    }
                } else {
                    printCor("\n\aResposta inv�lida! Digite apenas letras e que sejam de A at� E.\n", 12, 7); // Vermelho claro para Branco
                    system("pause");
                    system("cls");
                    setCor(10); // Verde claro
                    type(perguntas[i], 30);
                    printCor(opcoes[i], 6, 7); // Amarelo para Branco
                }
            }
        }

        printCor("Parab�ns! Voc� respondeu todas corretamente!\n", 10, 7); // Verde claro para Branco
        printf("A senha gerada �: ");
        printCor("%d\n", 2, 7, senha); // Verde para Branco
        system("pause");
        system("cls");
        break;
    }
}

void gabarito() {
    const char *perguntas[] = {
        "[1] Qual tipo armazena valores com ponto flutuante e maior precis�o?\n\n",
        "[2] Qual tipo de vari�vel serve para ler caracteres alfanum�ricos?\n\n",
        "[3] Qual desses N�O � um tipo de vari�vel da linguagem C?\n\n",
        "[4] Qual tipo de vari�vel armazena n�meros inteiros positivos e negativos?\n\n",
        "[5] Qual tipo de vari�vel � recomendado para armazenar textos (sequ�ncias de caracteres) em C?\n\n",
        "[6] Qual tipo de vari�vel em C � usado para armazenar n�meros inteiros muito grandes?\n\n"
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
        system("cls");
        setCor(11); // Aqua claro
        printf("%s", perguntas[i]);

        const char *op = opcoes[i]; // � usado ponteiro porque "opcoes" tamb�m � um
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
        system("pause");
    }
    system("cls");
}

void setCor(int cor) {
    SetConsoleTextAttribute(hConsole, cor);
}

void printCor(const char *texto, int cor, int corF, ...) {
    SetConsoleTextAttribute(hConsole, cor);
            
    // Esse ngc aqui em baixo eu n consegui fazer sozinho
    va_list args;
    va_start(args, corF);
    vprintf(texto, args);
    va_end(args);
    // Esse ngc encima 
    
    SetConsoleTextAttribute(hConsole, corF);   
}

void CleanIn(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Load(int ms, int Pcolor, int LoadColor) {
    SetConsoleTextAttribute(hConsole, Pcolor);
    printf("\nCarregando...\n");
    SetConsoleTextAttribute(hConsole, LoadColor);
    for(int i = 0; i <= 100; i++) {
        printf("\r[%3d%%]", i);
        fflush(stdout);
        Sleep(ms);
    }
    SetConsoleTextAttribute(hConsole, 7); // Branco
}