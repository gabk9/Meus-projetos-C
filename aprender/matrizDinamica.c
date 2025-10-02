#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CleanIn();

int main() {
    int **mat, i, j; // É usado ponteiro de um ponteiro porque é um array de duas dimensões
    int X_AXIS, Y_AXIS;

    printf("Me diga a largura: ");
    scanf("%d", &X_AXIS);
    CleanIn();

    printf("Me diga a altura: ");
    scanf("%d", &Y_AXIS);
    CleanIn();

    mat = malloc(Y_AXIS * sizeof(int*));// Matriz de "Y_AXIS" linhas para um ponteiro de um inteiro
    // mat = calloc(X_AXIS, sizeof(int*));

    for(i = 0; i < Y_AXIS; i++) {
        mat[i] = malloc(X_AXIS * sizeof(int ));
    }
    srand(time(NULL));

    for(i = 0; i < Y_AXIS; i++) {
        for(j = 0; j < X_AXIS; j++) {
            *(*(mat + i) + j) = rand() % 100;
            //mat[i][j] = rand() % 100;
        }
    }

    printf("\n");
    for(i = 0; i < Y_AXIS; i++) {
        for(j = 0; j < X_AXIS; j++) {
            printf("%2d ", *(*(mat + i) + j));
            // printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    
    for(i = 0; i < Y_AXIS; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}

void CleanIn() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}