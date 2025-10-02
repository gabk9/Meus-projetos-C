#include <stdio.h>

void bubbleSort(int array[], int tamanho);
void printArray(int array[], int tamanho);
int estaOrdenado(int array[], int tamanho);

int main() {
    int c[] = {2, 4, 1, 3, 5, 7, 8, 6, 9, 10};
    int tamanho = sizeof(c) / sizeof(c[0]);

    if (estaOrdenado(c, tamanho)) {
        printf("O array ja esta ordenado!!\n");
    } else {
        bubbleSort(c, tamanho);
    }

    printArray(c, tamanho);

    return 0;
}

void bubbleSort(int array[], int tamanho) {
    int trocou;
    for(int i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for(int j = 0; j < tamanho - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                trocou = 1;
            }
        }
        if(trocou == 0) {
            break;
        }
    }
}

int estaOrdenado(int array[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (array[i] > array[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void printArray(int array[], int tamanho) {
    for(int i = 0; i < tamanho; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}
