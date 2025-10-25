#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Y_AXIS 5
#define X_AXIS 6

typedef struct {
    int *data;
    int size;
} intArr;

void printArr(intArr arr);

int main() {
    intArr mat[Y_AXIS];
    srand(time(NULL));

    for (int i = 0; i < Y_AXIS; i++) {
        mat[i].data = calloc(X_AXIS, sizeof(int));
        mat[i].size = X_AXIS;
        if (!mat[i].data) {
            printf("Allocation Error!!\n");
            return 1;
        }
    }

    for (int i = 0; i < Y_AXIS; i++) 
        for (int j = 0; j < X_AXIS; j++) 
            mat[i].data[j] = rand() % 100;
        

    for (int i = 0; i < Y_AXIS; i++)
        printArr(mat[i]);

    for (int i = 0; i < Y_AXIS; i++)
        free(mat[i].data);

    return 0;
}

void printArr(intArr arr) {
    printf("[");
    for (int i = 0; i < arr.size; i++) {
        char *lastChar = (i == arr.size - 1) ? "" : ", ";
        printf("%2d%s", arr.data[i], lastChar);
    }
    printf("]\n");
}
