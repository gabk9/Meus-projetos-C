#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>
#include <stdarg.h>  // Necess�rio para va_list

HANDLE hConsole;
void typewriter(const char *texto, int ms);
void setCor(HANDLE hConsole, int cor);
void CleanIn();
void obterCaminhoArquivo(char* caminhoCompleto, size_t tamanho, const char* nomeArquivo);
void Incriptografar(HANDLE hConsole);
void printCor(HANDLE hConsole, const char *texto, int cor, int corF, ...);
void Desincriptografar(HANDLE hConsole);
void linha(HANDLE hConsole);

int main() { 
    setlocale(LC_ALL, "Portuguese_Brazil");
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int op;

    do {
        printCor(hConsole, "\n=======CIFRA DE C�SAR=======\n", 4, 1); // vermelho para Azul
        typewriter("[1] Incriptografar\n[2] Desincriptografar\n[3] Apagar dados\n[4] Sair\n", 25); 
        setCor(hConsole, 7); // Branco padr�o
        scanf("%d", &op);
        CleanIn();

        switch(op){ 
            case 1: Incriptografar(hConsole); break;
            case 2: Desincriptografar(hConsole); break;
            case 3: {
                char caminhoArquivo[MAX_PATH];
                obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
                FILE *arquivo = fopen(caminhoArquivo, "w"); 
                setCor(hConsole, 4); // Vermelho claro
                printf("Dados apagados com sucesso!!\n"); 
                setCor(hConsole, 7); // Branco padr�o
                fclose(arquivo);
                system("pause");
                system("cls");
                break;
            }
            case 4: 
                printCor(hConsole, "Saindo...", 4, 7); // Vermelho para Branco padr�o
                break; 
            default: 
                printCor(hConsole, "\n\aMe diga uma resposta v�lida!!\n", 12, 7); // Vermelho claro para Branco padr�o
                system("pause");
                system("cls");
        }
    } while(op != 4);
}

void Incriptografar(HANDLE hConsole) {
    system("cls");
    char caminhoArquivo[MAX_PATH];
    obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
    FILE *arquivo = fopen(caminhoArquivo, "a");
    int dslc;
    char palavra[100], resultado[100];

    system("cls");
    printf("Me diga o ");
    printCor(hConsole, "deslocamento", 2, 7); // Verde para Branco padr�o
    printf(": ");
    scanf("%d", &dslc);
    CleanIn();

    printf("Me Diga a ");
    printCor(hConsole, "palavra", 5, 7); // Roxo para Branco padr�o
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

    linha(hConsole);

    printf("Palavra criptografada: ");
    printCor(hConsole, "%s\n\n", 6, 7, resultado); // Amarelo para Branco padr�o

    char op;
    do {
        printf("Deseja gravar os dados? ("); 
        printCor(hConsole, "s", 2, 7);
        printf("/"); 
        printCor(hConsole, "n", 4, 7);
        printf(") ");
        scanf(" %c", &op);
        CleanIn();

        if(tolower(op) == 's') {
            fprintf(arquivo, "%s\n", resultado);
            printCor(hConsole, "\nDados registrados com sucesso!!\n", 2, 7); // Verde para Branco padr�o
        } else if(tolower(op) == 'n') {
            printCor(hConsole, "\nDados n�o registrados!!\n", 12, 7); // Vermelho claro para Branco padr�o
        } else {
            printCor(hConsole, "\aResposta inv�lida!!\n", 12, 7); // Vermelho claro para Branco padr�o
            system("pause");
        }
    } while(tolower(op) != 's' && tolower(op) != 'n');

    fclose(arquivo);
    system("pause");
    system("cls");
}

void Desincriptografar(HANDLE hConsole) {
    system("cls");
    char resposta[20], palavra[100];
    char caminhoArquivo[MAX_PATH];
    FILE *arquivo = NULL;

    do {
        printf("Deseja inserir uma palavra incriptografada manualmente ou ler um arquivo? ("); 
        printCor(hConsole, "type", 2, 7);
        printf("/");
        printCor(hConsole, "read", 4, 7);
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
                printCor(hConsole, "\aErro ao abrir o arquivo para escrita!\n", 12, 7); // Vermelho claro para Branco padr�o
                system("pause");
                system("cls");
                return;
            }
            fprintf(arquivo, "%s\n", palavra);
            fclose(arquivo);

        } else if (result2 == 0) {
            obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo), "CifraCesar.txt");
        } else {
            printCor(hConsole, "\aOp��o inv�lida! Tente novamente.\n", 12, 7);
        }

    } while (strcasecmp(resposta, "type") != 0 && strcasecmp(resposta, "read") != 0);

    // Agora vamos abrir o arquivo para leitura e descriptografar tudo
    arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printCor(hConsole, "\aErro ao abrir o arquivo para leitura!\n", 12, 7); // Vermelho claro para Branco padr�o
        system("pause");
        system("cls");
        return;
    }

    // Verificar se o arquivo est� vazio
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    if (tamanho == 0) {
        printCor(hConsole, "\aO arquivo est� vazio!\n", 12, 7); // Vermelho claro para Branco padr�o
        fclose(arquivo);
        system("pause");
        system("cls");
        return;
    }

    printf("\n");

    char linhaOriginal[100];
    while (fgets(linhaOriginal, sizeof(linhaOriginal), arquivo) != NULL) {
        linhaOriginal[strcspn(linhaOriginal, "\n")] = '\0';

        printCor(hConsole, "Tentando descriptografar: %s\n\n", 3, 7, linhaOriginal); // Aqua para Branco padr�o

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

            printCor(hConsole, "Deslocamento %2d: ", 6, 7, dslc); // Amarelo para Branco padr�o
            printf("%s\n", tentativa);
        }
        puts("");
    }

    fclose(arquivo);
    system("pause");
    system("cls");
}

void setCor(HANDLE hConsole, int cor) {
    SetConsoleTextAttribute(hConsole, cor);
}

void printCor(HANDLE hConsole, const char *texto, int cor, int corF, ...) {
    SetConsoleTextAttribute(hConsole, cor);
            
    // Esse neg�cio aqui em baixo eu admito que peguei no GPT
    va_list args;
    va_start(args, corF);
    vprintf(texto, args);
    va_end(args);
    // Esse neg�cio em cima 
    
    SetConsoleTextAttribute(hConsole, corF);   
}

void typewriter(const char *texto, int ms) {
    for(int i = 0; texto[i] != '\0'; i++) {
        putchar(texto[i]);
        Sleep(ms);
    }
}

void CleanIn() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void linha(HANDLE hConsole) {
    printCor(hConsole, "\n=================================\n", 11, 7); // Aqua claro para Branco padr�o
}

// Gambiarra para fazer funcionar no VScode, (feita com GPT)
void obterCaminhoArquivo(char* caminhoCompleto, size_t tamanho, const char* nomeArquivo) {
    char caminhoExe[MAX_PATH];
    GetModuleFileName(NULL, caminhoExe, MAX_PATH);

    char* p = strrchr(caminhoExe, '\\');
    if (p) {
        *(p + 1) = '\0';  // Corta ap�s a �ltima barra
    }

    snprintf(caminhoCompleto, tamanho, "%s%s", caminhoExe, nomeArquivo);
}
