#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER 0x80
typedef struct {
    int *data;
    int size;
} intArr;

int readInt(void);
intArr swap(intArr arr);
void printArr(const intArr arr);
void arrcpy(intArr *dest, const intArr src);

int main(void) {
    intArr *mat;
    size_t n;

    do {
        printf("Enter matrix size (N x N): ");
        n = readInt();
    
        if (n < 2 || n > 7) {
            fprintf(stderr, "Error: invalid size\n");
        }
    } while (n < 2 || n > 7);

    mat = calloc(n, sizeof(intArr));

    if (!mat) {
        perror("\nError: Memory allocation error\n");
        return 1;
    }

    for (size_t i = 0; i < n; i++) {
        mat[i].size = n;
        mat[i].data = calloc(n, sizeof(int));
        if (!mat[i].data) {
            perror("\nError: Memory allocation error\n");
            return 1;
        }
    }

    printf("\n");
    for(size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            printf("Enter the number [%zu][%zu]: ", i, j);
            mat[i].data[j] = readInt();
        }
    }

    intArr *copy = calloc(n, sizeof(intArr));

    if (!copy) {
        perror("\nError: Memory allocation error\n"); 
        return 1; 
    }

    for (size_t i = 0; i < n; i++) {
        copy[i] = swap(mat[i]);
    }

    printf("\nBefore:\n");
    for (size_t i = 0; i < n; i++) {
        printArr(mat[i]);
    }

    printf("\nAfter:\n");
    for (size_t i = 0; i < n ; i++) {
        printArr(copy[i]);
    }

    for (size_t i = 0; i < n; i++) {
        free(mat[i].data);
    }
    free(mat);
    
    for (size_t i = 0; i < n; i++) {
        free(copy[i].data);
    }
    free(copy);

    return 0;
}

intArr swap(intArr arr) {
    intArr copy;
    arrcpy(&copy, arr);

    int end = copy.size - 1;
    int temp = copy.data[end];
    copy.data[end] = copy.data[0];
    copy.data[0] = temp;

    return copy;
}

void arrcpy(intArr *dest, const intArr src) {
    dest->size = src.size;
    dest->data = malloc(src.size * sizeof(int));

    if (!dest->data) { 
        perror("\nError: Memory allocation error\n"); 
        exit(1); 
    }

    for (size_t i = 0; i < src.size; i++)
        dest->data[i] = src.data[i];
}

void printArr(const intArr arr) {
    printf("[");
    for (size_t i = 0; i < arr.size; i++) {
        char *lastChar = (i == arr.size - 1) ? "" : ", ";
        printf("%d%s", arr.data[i], lastChar);
    }
    printf("]\n");
}

int readInt(void) {
    char buffer[BUFFER];
    int value;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            perror("Error reading input");
            exit(1);
        }
        if (sscanf(buffer, "%d", &value) == 1) {
            return value;
        }
        fprintf(stderr, "Invalid input. Please enter an integer: ");
    }
}