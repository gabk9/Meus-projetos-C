#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100], nome[100];
    int id;

    do{
        printf("Me diga sua Idade e seu Nome: ");

        fgets(buffer, sizeof(buffer), stdin);
        int qtd = sscanf(buffer, "%d %s", &id, nome);

        (qtd == 2) ? printf("\nValor valido!\nIdade: %d\nNome: %s\nValores lidos: %d\n\n", id, nome, qtd): printf("Valor invalido ou insuficiente!\n\n");
    } while (1);
    
    return 0;
}