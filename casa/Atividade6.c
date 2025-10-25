#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void BubbleSort(int var[], int tamanho);
void printArray(int var[], int tamanho);
void printParArray(int var[], int tamanho);
void CleanIn();

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int *c, tam = 0;

    printf("Me diga o tamanho do array: ");
    scanf("%d", &tam);
    CleanIn();

    c = calloc(tam, sizeof(int));
    if (!c) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("\nMe diga %d números para organizar:\n", tam);
    for (int i = 0; i < tam; i++) {
        printf("[%d]: ", i + 1);
        scanf("%d", &c[i]);
        CleanIn();
    }

    printf("\nArray antes de organizar:\n");
    printArray(c, tam);

    BubbleSort(c, tam);

    printf("Array depois de organizar:\n");
    printArray(c, tam);

    printParArray(c, tam);

    free(c);
    return 0;
}

void BubbleSort(int var[], int tamanho){
    int trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int houveTroca = 0;
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (var[j] > var[j + 1]) {
                int aux = var[j];
                var[j] = var[j + 1];
                var[j + 1] = aux;
                trocas++;
                houveTroca = 1;
            }
        }
        if (!houveTroca) {
            printf("\n\nNão precisa ser feita nenhuma alteração!\n");
            break;
        }
    }
    printf("\n\nForam feitas %d trocas!\n", trocas);
}

void printArray(int var[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", var[i]);
    }
    printf("\n");
}

void printParArray(int var[], int tamanho) {
    printf("\nArray somente com números pares:\n");
    for(int i = 0; i < tamanho; i++) {
        if(var[i] % 2 == 0) {
            printf("%d ", var[i]);
        }
    }
    printf("\n");
}

void CleanIn() {
    int c;
    while((c = getchar()) != '\n' && c != EOF); 
}