#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
    HANDLE hConsole;
    #define CLEAR "cls"
    #define Pause(void) system("pause")
    #define SleepMS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define CLEAR "clear"
    #define Pause(void) do { \
        printf("\nPressione ENTER para continuar..."); \
        getchar(); \
    } while(0)
    #define SleepMS(ms) usleep((ms) * 1000)
    #define MAX_PATH 0x104
#endif

void typewriter(const char *texto, int ms);
void setCor(int cor);
void CleanIn();
void obterCaminhoArquivo(char* caminhoCompleto, size_t tamanho, const char* nomeArquivo);
void Incriptografar();
void printCor(const char *texto, int cor, int corF, ...);
void Desincriptografar();
void linha();

int main() { 
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    setlocale(LC_ALL, "Portuguese_Brazil");
    int op;

    do {
        printCor("\n=======CIFRA DE C�SAR=======\n", 4, 1); // vermelho para Azul
        typewriter("[1] Incriptografar\n[2] Desincriptografar\n[3] Apagar dados\n[4] Sair\n", 25); 
        setCor(7); // Branco padr�o
        scanf("%d", &op);
        CleanIn();

        switch(op){ 
            case 1: Incriptografar(); break;
            case 2: Desincriptografar(); break;
            case 3: {
                char caminhoArquivo[MAX_PATH];
                obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
                FILE *arquivo = fopen(caminhoArquivo, "w"); 
                setCor(4); // Vermelho claro
                printf("Dados apagados com sucesso!!\n"); 
                setCor(7); // Branco padr�o
                fclose(arquivo);
                Pause();
                system(CLEAR);
                break;
            }
            case 4: 
                printCor("Saindo...", 4, 7); // Vermelho para Branco padr�o
                break; 
            default: 
                printCor("\n\aMe diga uma resposta v�lida!!\n", 12, 7); // Vermelho claro para Branco padr�o
                Pause();
                system(CLEAR);
        }
    } while(op != 4);
}

void Incriptografar() {
    system(CLEAR);
    char caminhoArquivo[MAX_PATH];
    obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
    FILE *arquivo = fopen(caminhoArquivo, "a");
    int dslc;
    char palavra[100], resultado[100];

    system(CLEAR);
    printf("Me diga o ");
    printCor("deslocamento", 2, 7); // Verde para Branco padr�o
    printf(": ");
    scanf("%d", &dslc);
    CleanIn();

    printf("Me Diga a ");
    printCor("palavra", 5, 7); // Roxo para Branco padr�o
    printf(": ");
    fgets(palavra, sizeof(palavra), stdin);
    palavra[strcspn(palavra, "\n")] = '\0';

    for(int i = 0; palavra[i] != '\0'; i++) {
        char c = palavra[i];
        if(c >= 'a' && c <= 'z') {
            resultado[i] = ((c - 'a' + dslc) % 26) + 'a';
        } else if(c >= 'A' && c <= 'Z') {
            resultado[i] = ((c - 'A' + dslc) % 26) + 'A';
        } else {
            resultado[i] = c;
        }
    }

    resultado[strlen(palavra)] = '\0';  // Finaliza a string "resultado" corretamente, igualando o tamanho da palavra original 

    linha();

    printf("Palavra criptografada: ");
    printCor("%s\n\n", 6, 7, resultado); // Amarelo para Branco padr�o

    char op;
    do {
        printf("Deseja gravar os dados? ("); 
        printCor("s", 2, 7);
        printf("/"); 
        printCor("n", 4, 7);
        printf(") ");
        scanf(" %c", &op);
        CleanIn();

        if(tolower(op) == 's') {
            fprintf(arquivo, "%s\n", resultado);
            printCor("\nDados registrados com sucesso!!\n", 2, 7); // Verde para Branco padr�o
        } else if(tolower(op) == 'n') {
            printCor("\nDados n�o registrados!!\n", 12, 7); // Vermelho claro para Branco padr�o
        } else {
            printCor("\aResposta inv�lida!!\n", 12, 7); // Vermelho claro para Branco padr�o
            Pause();
        }
    } while(tolower(op) != 's' && tolower(op) != 'n');

    fclose(arquivo);
    Pause();
    system(CLEAR);
}

void Desincriptografar() {
    system(CLEAR);
    char resposta[20], palavra[100];
    char caminhoArquivo[MAX_PATH];
    FILE *arquivo = NULL;

    do {
        printf("Deseja inserir uma palavra incriptografada manualmente ou ler um arquivo? ("); 
        printCor("type", 2, 7);
        printf("/");
        printCor("read", 4, 7);
        printf(") ");
        fgets(resposta, sizeof(resposta), stdin);
        resposta[strcspn(resposta, "\n")] = '\0';

        int result = strcasecmp(resposta, "type");
        int result2 = strcasecmp(resposta, "read");

        if (result == 0) {
            printf("Digite a palavra incriptografada: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            // Salvar no arquivo
            obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
            arquivo = fopen(caminhoArquivo, "a");
            if (arquivo == NULL) {
                printCor("\aErro ao abrir o arquivo para escrita!\n", 12, 7); // Vermelho claro para Branco padr�o
                Pause();
                system(CLEAR);
                return;
            }
            fprintf(arquivo, "%s\n", palavra);
            fclose(arquivo);

        } else if (result2 == 0) {
            obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
        } else {
            printCor("\aOp��o inv�lida! Tente novamente.\n", 12, 7);
        }

    } while (strcasecmp(resposta, "type") != 0 && strcasecmp(resposta, "read") != 0);

    // Agora vamos abrir o arquivo para leitura e descriptografar tudo
    arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printCor("\aErro ao abrir o arquivo para leitura!\n", 12, 7); // Vermelho claro para Branco padr�o
        Pause();
        system(CLEAR);
        return;
    }

    // Verificar se o arquivo est� vazio
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    if (tamanho == 0) {
        printCor("\aO arquivo est� vazio!\n", 12, 7); // Vermelho claro para Branco padr�o
        fclose(arquivo);
        Pause();
        system(CLEAR);
        return;
    }

    printf("\n");

    char linhaOriginal[100];
    while (fgets(linhaOriginal, sizeof(linhaOriginal), arquivo) != NULL) {
        linhaOriginal[strcspn(linhaOriginal, "\n")] = '\0';

        printCor("Tentando descriptografar: %s\n\n", 3, 7, linhaOriginal); // Aqua para Branco padr�o

        for (int dslc = 1; dslc < 26; dslc++) {
            char tentativa[100];

            for (int i = 0; linhaOriginal[i] != '\0'; i++) {
                char c = linhaOriginal[i];
                if (c >= 'a' && c <= 'z') {
                    tentativa[i] = ((c - 'a' - dslc + 26) % 26) + 'a';
                } else if (c >= 'A' && c <= 'Z') {
                    tentativa[i] = ((c - 'A' - dslc + 26) % 26) + 'A';
                } else {
                    tentativa[i] = c;
                }
            }
            tentativa[strlen(linhaOriginal)] = '\0';

            printCor("Deslocamento %2d: ", 6, 7, dslc); // Amarelo para Branco padr�o
            printf("%s\n", tentativa);
        }
        puts("");
    }

    fclose(arquivo);
    Pause();
    system(CLEAR);
}

void setCor(int cor) {
    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, color);
    #else
        switch(cor) {
            case 0:    printf("\033[30m"); break;
            case 1:    printf("\033[34m"); break;
            case 2:    printf("\033[32m"); break;
            case 3:    printf("\033[36m"); break;
            case 4:    printf("\033[31m"); break;
            case 5:    printf("\033[35m"); break;
            case 6:    printf("\033[33m"); break;
            case 7:    printf("\033[37m"); break;
            case 8:    printf("\033[90m"); break;
            case 9:    printf("\033[94m"); break;
            case 10:   printf("\033[92m"); break;
            case 11:   printf("\033[96m"); break;
            case 12:   printf("\033[91m"); break;
            case 13:   printf("\033[95m"); break;
            case 14:   printf("\033[93m"); break;
            case 15:   printf("\033[97m"); break;
            default:   printf("\033[0m");  break;
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
void typewriter(const char *texto, int ms) {
    while (*texto) {
        putchar(*texto);
        fflush(stdout);
        SleepMS(ms);
        texto++;
    }
}

void CleanIn() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void linha() {
    printCor("\n=================================\n", 11, 7); // Aqua claro para Branco padr�o
}

// Gambiarra para fazer funcionar no VScode, (feita com GPT)
void obterCaminhoArquivo(char* caminhoCompleto, size_t tamanho, const char* nomeArquivo) {
#ifdef _WIN32
    char pathEXE[MAX_PATH_LEN];
    GetModuleFileName(NULL, pathEXE, MAX_PATH_LEN);

    char* p = strrchr(pathEXE, '\\');
    if (p) {
       *(p + 1) = '\0';
    }

    snprintf(caminhoCompleto, tamanho, "%s%s", pathEXE, nomeArquivo);
#else

    snprintf(caminhoCompleto, tamanho, "./%s", nomeArquivo);
#endif
}
