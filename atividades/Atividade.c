#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

int contarLinhas(const char *nomeArquivo);
int sobrescreverNumeroNoArquivo(const char *nomeArquivo);
int linhaVazia(const char *linha);

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    int linhas = contarLinhas("Atividade.txt");

    if (sobrescreverNumeroNoArquivo("Atividade.txt") == 0) {
        printf("Arquivo sobrescrito com números no início das linhas.\n");
    }

    printf("O seu arquivo tem %d linhas\n", linhas);

    return 0;
}

int linhaVazia(const char *linha) {
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n' && linha[i] != '\r') {
            return 0; // tem texto
        }
    }
    return 1; // só espaços, tab ou newline
}

int contarLinhas(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    int linhas = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        linhas++;
    }

    fclose(arquivo);
    return linhas;
}

int sobrescreverNumeroNoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r+"); // leitura e escrita
    if (!arquivo) {
        printf("Erro ao abrir arquivo.\n");
        return -1;
    }

    char linha[1024];
    int numeroLinha = 1;

    while (1) {
        long pos = ftell(arquivo);
        if (!fgets(linha, sizeof(linha), arquivo)) {
            break;
        }

        if (!linhaVazia(linha)) {
            fseek(arquivo, pos, SEEK_SET);
            fprintf(arquivo, "%2d ", numeroLinha);
            numeroLinha++;
        }
    }

    fclose(arquivo);
    return 0;
}
