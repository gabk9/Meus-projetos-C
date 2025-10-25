#include <stdio.h>

#define PLANOS 2
#define LINHAS 3
#define COLUNAS 4

void BubbleSort(int var[], int tam);
void printArray(int var[], int tam);

int main() {
    int matriz[PLANOS][LINHAS][COLUNAS] = {
        {
            {12, 7, 9, 15},
            {3, 14, 6, 8},
            {11, 2, 10, 5}
        },
        {
            {4, 13, 1, 16},
            {7, 8, 12, 3},
            {9, 14, 2, 10}
        }
    };

    int tam = PLANOS * LINHAS * COLUNAS;
    int vetor[tam];


    int idx = 0;
    for (int i = 0; i < PLANOS; i++) {
        for (int j = 0; j < LINHAS; j++) {
            for (int k = 0; k < COLUNAS; k++) {
                vetor[idx++] = matriz[i][j][k];
            }
        }
    }

    BubbleSort(vetor, tam);

    printf("Matriz 3D organizada do menor para o maior (em vetor):\n");
    printArray(vetor, tam);

    return 0;
}

void BubbleSort(int var[], int tam) {
    int aux, houveTroca;
    for (int i = 0; i < tam - 1; i++) {
        houveTroca = 0;
        for (int j = 0; j < tam - i - 1; j++) {
            if (var[j] > var[j + 1]) {
                aux = var[j];
                var[j] = var[j + 1];
                var[j + 1] = aux;
                houveTroca = 1;
            }
        }
        if (!houveTroca) break;
    }
}

void printArray(int var[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%2d ", var[i]);
        if ((i + 1) % COLUNAS == 0) printf("\n");
        if ((i + 1) % (LINHAS * COLUNAS) == 0) printf("\n");
    }
}
