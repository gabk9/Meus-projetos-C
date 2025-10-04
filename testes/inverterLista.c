#include <stdio.h>
#include <stdlib.h>

int *invertArray(int *arr, int size);

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(list) / sizeof(int);

    int *Inverted = invertArray(list, len);

    printf("Array inverted:\n");
    for(int i = 0; i < len; i++) {
        printf("%d ", Inverted[i]);
    }

    free(Inverted);
    return 0;
}

int *invertArray(int *arr, int size) {
    int len = size, end, i, aux;
    int *newArr = malloc(size * sizeof(char));

    if(!newArr) {
        printf("Erro de alocação!\n");
        exit(1);
    }

    for(int i = 0; i < size; i++) {
        newArr[size - 1 - i] = arr[i];
    }

    return newArr;
}