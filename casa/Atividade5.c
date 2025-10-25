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

    float *c = calloc(tam, sizeof(float));  // c ainda � um ponteiro para float
    if (!c) {
        printf("Erro ao alocar mem�ria.\n");
        return 1;
    }

    printf("\nMe diga %d n�meros para organizar:\n", tam);
    for (int i = 0; i < tam; i++) {
        printf("[%d]: ", i + 1);
        scanf("%f", &c[i]);
        CleanIn();
    }

    bubbleSort(c, tam);

    printf("\nArray ordenado: ");
    printArray(c, tam);  // Adicionei a chamada para printArray para mostrar o array ordenado

    free(c);  // N�o se esque�a de liberar a mem�ria alocada

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
            printf("\n\nN�o precisa ser feita nenhuma altera��o!\n");
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
    while ((c = getchar()) != '\n' && c != EOF);  // Corrigi a condi��o do while
}
