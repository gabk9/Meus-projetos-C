#include <stdio.h>
#include <stdlib.h>

void CleanIn();
void printArr(int **arr, int len);
int *twosum(int **arr, int len, int target);

int main() {
    int arrSize, target;
    int **arr;

    printf("Type-in the array size: ");
    scanf("%d", &arrSize);
    CleanIn();

    arr = calloc(arrSize, sizeof(int *));
    if(!arr) {
        printf("\nAllocation Error!\n");
        return 1;
    }

    for(int i = 0; i < arrSize; i++) {
        printf("\nType-in a number: ");
        scanf("%d", &arr[i]);
        CleanIn();
    }

    printf("\nArray:\n");
    printArr(arr, arrSize);

    printf("\n\nTarget: ");
    scanf("%d", &target);
    CleanIn();



    return 0;
}

int *twosum(int **arr, int len, int target) {
    int **pos;
    for(int i = 0; i < len - 1; i++) {
        for(int j = 0; j < len - i - 1; j++) {
            if((arr[j] + arr[j + 1]) == target) {
                // TODO continue here
            }
        }
    }
}

void printArr(int **arr, int len) {
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

void CleanIn() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}