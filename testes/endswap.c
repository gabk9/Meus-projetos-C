#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#define BUFFER 0x80
#define MAXGEN 0xC8
#define MAXSIZE 0x14
#define DB (float)0x0400

typedef struct {
    int *data;
    int size;
} intArr;

intArr swap(intArr arr);
char *strcopy(char *src);
size_t strsiz(const char *str);
void printArr(const intArr arr);
void arrcpy(intArr *dest, const intArr src);
int strcomp(const char *str1, const char *str2);
void CleanStr(char *str, char target, char repl);
int input(char *buffer, int size, char *fmt, void *out);

int main(void) {
    intArr *mat;
    size_t n;
    char *buffer = calloc(BUFFER, sizeof(char));
    char *str = NULL; 
    double memStructs, memData, memTotal;
    srand(time(NULL));

    do {
        printf("Enter matrix size (N x N): ");
        input(buffer, BUFFER, "%zu", &n);
    
        if (n < 2 || n > MAXSIZE) {
            fprintf(stderr, "Error: invalid size\n");
        }
    } while (n < 2 || n > MAXSIZE);

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

    memStructs = n * sizeof(intArr);
    memData = n * n * sizeof(int);
    memTotal = memStructs + memData;

    printf("\nMemory allocated successfully!!\n");
    printf("Structs: %.2lfB, %.2lfKB\n", memStructs, memStructs / DB);
    printf("Data: %.2lfB, %.2lfKB\n", memData, memData / DB);
    printf("Total: %.2lfB, %.2lfKB\n\n", memTotal, memTotal / DB);

    printf("\n");
    for(size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            mat[i].data[j] = rand() % MAXGEN;
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
        printf("%3d%s", arr.data[i], lastChar);
    }
    printf("]\n");
}

char *strcopy(char *src) {
    int len = strsiz(src);
    char *dest = malloc((len + 1) * sizeof(char));

    if (!dest) {
        printf("Error: allocation error!!");
        exit(1);
    }

    for (int i = 0; i <= len; i++) {
        dest[i] = src[i];
    }
    return dest;
}

size_t strsiz(const char *str) {
    int i = 0;
    while (str[i]) i++;
    return i;
}

void CleanStr(char *str, char target, char repl) {
    for (size_t i = 0; i < str[i]; i++) 
        if (str[i] == target) 
            str[i] = repl;
}

int strcomp(const char *str1, const char *str2) {
    size_t i = 0;
    while (str1[i] && str2[i]) {
        if (str1[i] != str2[i]) 
            return 1;
        i++;
    }
    return (str1[i] == str2[i]) ? 0 : 1;
}

int input(char *buffer, int size, char *fmt, void *out) {
        while (1) {
        if (!fgets(buffer, size, stdin))
            return 0;
    
        CleanStr(buffer, '\n', '\0');

        if (strcomp(fmt, "%s") == 0) {
            *(char **)out = strcopy(buffer);
            return 1;
        }
        else if (sscanf(buffer, fmt, out) == 1)
            return 1;
        
        else
            printf("Invalid input, try again: ");
    
    }
}