#include <stdio.h>

void ReverseBubbleSort(int array[], int size);
void printArray(int array[], int size);

int main() {
    int c[] = {2, 4, 1, 3, 5, 7, 8, 6, 9, 10};
    int size = sizeof(c) / sizeof(c[0]);

    ReverseBubbleSort(c, size);
    printArray(c, size);

    return 0;
}

void ReverseBubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] < array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int array[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}