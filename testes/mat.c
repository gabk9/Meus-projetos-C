#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Y_AXIS 25
#define X_AXIS 25

int main() {
    int **mat = calloc(Y_AXIS, sizeof(int *));
    srand(time(NULL));
    
    if(!mat) {
        printf("Allocation Error!!\n");
        return 1;
    }
    
    for(int i = 0; i < Y_AXIS; i++) {
        mat[i] = calloc(X_AXIS, sizeof(int));
        if(!mat[i]) {
            printf("Allocation Error!!\n");
            return 1;
        }
    }

    for(int i = 0; i < Y_AXIS; i++) {
        for(int j = 0; j < X_AXIS; j++) {
            *(*(mat + i) + j) = rand() % 100;
        }
    }

    printf("\n");
    for(int i = 0; i < Y_AXIS; i++) {
        for(int j = 0; j < X_AXIS; j++) {
            printf("%2d ", *(*(mat + i) + j));
        }
        printf("\n");
    }

    for(int i = 0; i < Y_AXIS; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}