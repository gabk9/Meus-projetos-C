#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct intArr {
    int *data;
    int size;
} intArr;

int isalldigit(char *str);
void printArr(intArr *arr);
void charRm(char *str, int target);
void readNum(intArr *arr, char *buffer, int buffer_size);

int main(void) {
    intArr *mat[0x2];

    for (int i = 0; i < 2; i++) {
        mat[i] = malloc(sizeof(intArr));
        if (!mat[i]) {
            printf("Error: memory allocation error\n");
            return 1;
        }
    }

    char buffer[0x100];
    int i = 0;

    while (1) {
        printf("Enter the %s array size: ", (i == 0) ? "first" : "second");
        if(!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Errro: input error\n\n");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        if (!isalldigit(buffer)) {
            printf("Error: invalid datatype\n\n");
            continue;
        }

        int size = atoi(buffer);

        if (size <= 0 || size > 100) {
            printf("Error: the size must be greater than 0 and less or equal to 100\n\n");
            continue;
        }

        mat[i]->size = atoi(buffer);
        mat[i]->data = malloc(size * sizeof(int));

        if (!mat[i]->data) {
            printf("Error: memory allocation error!\n\n");
            return 1;
        }

        if (i == 1)
            break;
        
        i++;
    }

    putchar('\n');

    readNum(mat[0], buffer, 0x100);

    putchar('\n');

    readNum(mat[1], buffer, 0x100);

    int biggest = (mat[0]->size > mat[1]->size) ? mat[0]->size : mat[1]->size;

    intArr result;
    result.data = malloc((biggest + 1) * sizeof(int));
    result.size = biggest;

    if (!result.data) return 1;

    int carry = 0;

    for (int i = 0; i < biggest; i++) {
        int a = (i < mat[0]->size) ? mat[0]->data[i] : 0;
        int b = (i < mat[1]->size) ? mat[1]->data[i] : 0;

        int sum = a + b + carry;

        result.data[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry) {
        result.data[biggest] = carry;
        result.size++;
    }

    printArr(mat[0]);
    printArr(mat[1]);
    puts("--------------------");
    printArr(&result);

    return 0;
}

void printArr(intArr *arr) {
    putchar('[');
    for (int i = 0; i < arr->size; i++) {
        char *lastChr = (i >= arr->size - 1) ? "" : ", ";
        printf("%d%s", arr->data[i], lastChr);
    }
    puts("]");
}

void readNum(intArr *arr, char *buffer, int buffer_size) {
    for (int i = 0; i < arr->size;) {
        printf("Enter item n%d: ", i + 1);

        if (!fgets(buffer, buffer_size, stdin)) {
            printf("Errro: input error!\n\n");
            continue;
        }
        
        buffer[strcspn(buffer, "\n")] = '\0';

        if (!isalldigit(buffer)) {
            printf("Error: invalid datatype\n\n");
            continue;
        }
        
        int num = atoi(buffer);

        if (num < 0 || num > 9) {
            printf("Error: the at least one item of the result is negative or greater than 10\n\n");
            continue;
        }

        arr->data[i] = num;
        i++;
    }
}

void charRm(char *str, int target) {
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (str[i] != (char)target) {
            str[j++] = str[i];
        }
        i++;
    }

    str[j] = '\0';
}

int isalldigit(char *str) {
    charRm(str, ' ');
    int i = (str[0] == '-') ? 1 : 0;
    for (; str[i]; i++) {
        if (!(str[i] >= 0x30 && str[i] <= 0x39)) {
                return 0;
        }
    }
    return 1;
}