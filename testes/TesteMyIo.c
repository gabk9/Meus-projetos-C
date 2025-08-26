#include "../BIBLIOTECAS/MEU_IO/MyIo.h"
#include <locale.h>
#include <stdio.h>
#include <windows.h>

int main() {
    system("chcp 65001");
    setlocale(LC_ALL, "Portuguese_Brazil");
    int nInteiro; 
    char letra, nome[100];
    float preco;

    printf("\nMe diga um n�mero: ");
    readInt(&nInteiro, 12);
    printf("N�mero digitado: %d\n\n", nInteiro);

    printf("Me diga uma letra: ");
    readChar(&letra, 12);
    printf("Letra digitada %c\n\n", letra);

    printf("Digite seu nome: ");
    readString(nome, sizeof(nome), 12);
    printf("Ol�, %s!\n", nome);

    printf("\nDigite um n�mero float: ");
    readFloat(&preco, 12);
    printf("Voc� digitou: %.2f\n", preco);

    return 0;
}