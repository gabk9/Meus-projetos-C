#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR (1ULL << 7)

void printArr(int *arr, size_t size);
int input(size_t size, const char *fmt, void *out);
void unset(void **src, void *target, size_t elem_size, size_t *count);

int main(void) {
    int *arr, target;
    size_t n;

    printf("Enter the array size: ");
    input(MAXCHAR, "%zu", &n);

    arr = calloc(n, sizeof(int));

    if (!arr) {
        perror("Memory allocation error!!");
        return 1;
    }

    printf("\n");
    for (size_t i = 0; i < n; i++) {
        printf("Enter the %zu-th number of the array: ", i + 1);
        input(MAXCHAR, "%d", &arr[i]);
    }

    printf("\nArray before: ");
    printArr(arr, n);
    
    printf("\nEnter the number to remove:  ");
    input(MAXCHAR, "%d", &target);

    unset((void **)&arr, &target, sizeof(int), &n);

    printf("\nArray after: ");
    printArr(arr, n);

    free(arr);

    return 0;
}

void printArr(int *arr, size_t size) {
    printf("[");
    for (size_t i = 0; i < size; i++) {
        char *lastChar = (i == size - 1) ? "" : ", ";
        printf("%d%s", arr[i], lastChar);
    }
    printf("]\n");
}

void unset(void **src, void *target, size_t elem_size, size_t *count) {
    unsigned char *arr = *src;

    for (size_t i = 0; i < *count; i++) {
        if (memcmp(arr + i * elem_size, target, elem_size) == 0) {
            memmove(arr + i * elem_size,
                    arr + (i + 1) * elem_size,
                    (*count - i - 1) * elem_size);

            (*count)--;

            *src = realloc(*src, (*count) * elem_size);
            return;
        }
    }
}

int input(size_t size, const char *fmt, void *out) {
    char *buffer = calloc(MAXCHAR, 1);

    while (1) {
        if (!fgets(buffer, size, stdin)) {
            perror("Input error!!\n");
            return 1;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(fmt, "%s") == 0) {
            strcpy(out, buffer);
            return 0;   
        }

        if (sscanf(buffer, fmt, out) != 1) {
            printf("Wrong input, enter again: ");
            continue;
        }
        return 0;
    }

}