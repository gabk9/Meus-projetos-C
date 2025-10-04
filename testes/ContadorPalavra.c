#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>

void obterCaminhoArquivo(char* caminhoCompleto, size_t tamanho);

int main() {
    int c, word = 0, inword = 0;
    setlocale(LC_ALL, "Portuguese_Brazil");  // faltava ponto e vírgula

    char caminhoArquivo[MAX_PATH];
    obterCaminhoArquivo(caminhoArquivo, sizeof(caminhoArquivo));

    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado!\n");
        system("pause");
        return 1;  // encerra o programa
    }

    // Exibe conteúdo do arquivo
    char linha[100];
    printf("\n===== Dados do Arquivo =====\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    // Após ler o arquivo até o final, retorna para o início para contar palavras
    rewind(arquivo);

    while((c = fgetc(arquivo)) != EOF) {
        if (isspace(c)) {
            inword = 0;
        } else if (!inword) {
            inword = 1;
            word++;
        }
    }

    fclose(arquivo);

    printf("\nNúmero de palavras: %d\n", word);
    system("pause");
    return 0;
}

void obterCaminhoArquivo(char* caminhoCompleto, size_t tamanho) {
    char caminhoExe[MAX_PATH];
    GetModuleFileName(NULL, caminhoExe, MAX_PATH);

    // Remove o nome do exe do caminho
    char* p = strrchr(caminhoExe, '\\');
    if (p) {
        *(p + 1) = '\0'; // deixa só o caminho até a pasta
    }

    snprintf(caminhoCompleto, tamanho, "%sAtividade4.txt", caminhoExe);
}