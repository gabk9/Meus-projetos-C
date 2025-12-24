#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void bubbleSort(float v[], int size);
void printArray(float v[], int size);
void CleanIn();

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int tam = 0;  // Alterei para int

    printf("Me diga o tamanho do array: ");
    scanf("%d", &tam);
    CleanIn();

    float *c = calloc(tam, sizeof(float));  // c ainda é um ponteiro para float
    if (!c) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("\nMe diga %d números para organizar:\n", tam);
    for (int i = 0; i < tam; i++) {
        printf("[%d]: ", i + 1);
        scanf("%f", &c[i]);
        CleanIn();
    }

    bubbleSort(c, tam);

    printf("\nArray ordenado: ");
    printArray(c, tam);  // Adicionei a chamada para printArray para mostrar o array ordenado

    free(c);  // Não se esqueça de liberar a memória alocada

    return 0;
}

void bubbleSort(float v[], int size) {
    int houveTroca = 0, trocas = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                float aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;

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

void printArray(float v[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", v[i]);
    }
    printf("\n");
}

void CleanIn() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Corrigi a condição do while
}
