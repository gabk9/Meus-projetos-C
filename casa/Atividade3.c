#include <stdio.h>

void BubbleSort(int var[], int tamanho);
void printArray(int var[], int tamanho);

int main() {
    int c[] = {2, 4, 1, 3, 5, 7, 8, 6, 9, 10};
    int tamanho = sizeof(c) / sizeof(c[0]);

    printf("Array antes de organizar:\n");   
    printArray(c, tamanho);
    
    BubbleSort(c, tamanho);
    printArray(c, tamanho);

    return 0;
}

void BubbleSort(int var[], int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho - 1; i++) {
        for(int j = 0; j < tamanho - i - 1; j++) {
            if(var[j] > var[j + 1]) {
                int aux = var[j];
                var[j] = var[j + 1];
                var[j + 1] = aux;
            }
        }
        contador++;
    }
    printf("\n\nForam feitas %d trocas!\n", contador);
}

void printArray(int var[], int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", var[i]);
    }
}