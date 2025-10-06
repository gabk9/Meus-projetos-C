#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} intArr;

void printArr(intArr arr);
void extend(intArr *dest, const intArr *src);

int main(void) {
    int data1[] = {1, 2, 3, 4, 5};
    int data2[] = {6, 7, 8, 9, 10};

    intArr arr1 = {malloc(5 * sizeof(int)), 5};
    intArr arr2 = {data2, 5};

    for (int i = 0; i < arr1.size; i++) arr1.data[i] = data1[i];

    printf("1-st array:\n");
    printArr(arr1);

    printf("\n2-nd array:\n");
    printArr(arr2);

    printf("\narr1 concatenated with arr2:\n");
    extend(&arr1, &arr2);
    printArr(arr1);

    return 0;
}

void extend(intArr *dest, const intArr *src) {
    dest->data = realloc(dest->data, (dest->size + src->size) * sizeof(int));

    if (!dest->data) {
        fprintf(stderr, "Memory allocation error!!\n");
        exit(1);
    }

    for (int i = 0; i < src->size; i++) {
        dest->data[dest->size + i] = src->data[i];
    }

    dest->size += src->size;
}

void printArr(intArr arr) {
    printf("[");
    for (size_t i = 0; i < arr.size; i++) {
        char *lastChar = (i == arr.size - 1) ? "" : ", ";
        printf("%d%s", arr.data[i], lastChar);
    }
    printf("]\n");
}