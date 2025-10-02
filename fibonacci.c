#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
    int *data;
    int size; 
} intArr;

intArr fib(uint64_t n);
void printarr(intArr *arr);
void append(intArr *arr, int new);

int main(void) {
    uint64_t num;

    printf("Enter a number: ");
    scanf("%" PRIu64, &num);

    intArr array = fib(num);
    printf("Fibonacci sequence up to the %" PRIu64"-th number: ", num);
    printarr(&array);

    return 0;
}

intArr fib(uint64_t n) {
    intArr seq = {NULL, 0};
    if (n <= 0) 
        return seq;
    else if (n == 1) {
        append(&seq, 0);
        return seq;
    }
    else if (n == 2) {
        append(&seq, 0);
        append(&seq, 1);
        return seq;
    } 
    else {
        seq = fib(n - 1);
        append(&seq, seq.data[seq.size - 1] + seq.data[seq.size - 2]);
        return seq;
    }
}

void printarr(intArr *arr) {
    printf("[");
    for(int i = 0; i < arr->size; i++) {
        char *lastChar = (i == arr->size - 1) ? "" : ", ";
        printf("%d%s", arr->data[i], lastChar);
    }
    printf("]\n");
}

void append(intArr *arr, int new) {
    arr->data = realloc(arr->data, (arr->size + 1) * sizeof(int));
    if (!arr->data) {
        perror("Memory allocation error!!");
        exit(1);
    }

    arr->data[arr->size] = new;
    arr->size++;
}