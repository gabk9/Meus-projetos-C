#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} intArray;

void CleanIn(void);
void printArr(intArray arr);
intArray invertarr(intArray arr);
void arrcpy(intArray *dest, intArray src);

int main(void) {
    intArray array;

    printf("Enter array size: ");
    scanf("%d", &array.size);
    CleanIn();

    array.data = calloc(array.size, sizeof(int));
    if (!array.data) {
        printf("Allocation Error!!\n");
        return 1;
    }

    printf("\n");
    for (int i = 0; i < array.size; i++) {
        printf("Enter the %d-th number of the array: ", i + 1);
        scanf("%d", &array.data[i]);
        CleanIn();
    }

    printf("\nYour original Array: ");
    printArr(array);

    intArray newArr = invertarr(array);
    printf("\nThe same array but inverted: ");
    printArr(newArr);

    free(array.data);
    free(newArr.data);
    return 0;
}

void printArr(intArray arr) {
    printf("[");
    for (int i = 0; i < arr.size; i++) {
        char *lastChar = (i == arr.size - 1) ? "" : ", ";
        printf("%d%s", arr.data[i], lastChar);
    }
    printf("]\n");
}

void arrcpy(intArray *dest, intArray src) {
    dest->size = src.size;
    dest->data = malloc(src.size * sizeof(int));
    if (!dest->data) {
        printf("Allocation Error!!\n");
        exit(1);
    }
    for (int i = 0; i < src.size; i++) {
        dest->data[i] = src.data[i];
    }
}

intArray invertarr(intArray arr) {
    intArray cpy;
    arrcpy(&cpy, arr);

    for (int i = 0; i < cpy.size / 2; i++) {
        int temp = cpy.data[i];
        cpy.data[i] = cpy.data[cpy.size - i - 1];
        cpy.data[cpy.size - i - 1] = temp;
    }
    return cpy;
}

void CleanIn(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
