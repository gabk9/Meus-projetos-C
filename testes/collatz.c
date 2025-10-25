#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
} intArray;

intArray collatz(int n);
void printarr(intArray arr);
void append(intArray *arr, int new);

int main() {
    int num;
    intArray list;

    while (true) {
        printf("Enter a number (0 to exit): ");
        scanf("%d", &num);
    
        if (num == 0)
            break;

        list = collatz(num); 

        printf("Collatz sequence of the number: %d: ", num);
        printarr(list);
    }
    
    free(list.data);

    return 0;
}

intArray collatz(int n) {
    intArray seq = {NULL, 0};

    append(&seq, n);

    while (n != 1 && n != 0) {

        if (n % 2 == 0) 
            n /= 2;

        else 
            n = n * 3 + 1;
        
        append(&seq, n);
    }
    return seq;
}

void printarr(intArray arr) {
    printf("[");
    for(int i = 0; i < arr.size; i++) {
        char *lastChar = (i == arr.size - 1) ? "" : ", ";
        printf("%d%s", arr.data[i], lastChar);
    }
    printf("]\n");
}

void append(intArray *arr, int new) {
    arr->data = realloc(arr->data, (arr->size + 1) * sizeof(int));
    if (arr->data == NULL) {
        perror("Memory allocation error!!");
        exit(1);
    }

    arr->data[arr->size] = new;
    arr->size++;
}