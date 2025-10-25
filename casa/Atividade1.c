#include <stdio.h>

void bubbleSort(int array[], int tamanho);
void printArray(int array[], int tamanho);

int main() {
    int c[] = {2, 4, 1, 3, 5, 7, 8, 6, 9, 10};
    int tamanho = sizeof(c) / sizeof(c[0]);

    bubbleSort(c, tamanho);
    printArray(c, tamanho);

    return 0;
}

void bubbleSort(int array[], int tamanho) {
    for(int i = 0; i < tamanho - 1; i++) {
        for(int j = 0; j < tamanho - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int array[], int tamanho) {
    for(int i = 0; i < tamanho; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}