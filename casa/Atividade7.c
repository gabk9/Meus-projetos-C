#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 50

void CleanIn();
void CleanStr(char var[]);
void AlphaOrder(char **var, int size);
void printArray(char **var, int size);

int main() {
    char **word;
    int size;

    printf("How many words do u wanna use?? ");
    scanf("%d", &size);
    CleanIn();
    
    word = (char **)calloc(size, sizeof(char *));

    if(!word) {
        printf("\nMemory allocation error!!\n");
        return 1;
    }

    for(int i = 0; i < size; i++) {
        word[i] = (char *)calloc(MAX_STR, sizeof(char));
        if(!word[i]) {
            printf("\nError during allocation\n");
            return 1;
        }
    }

    printf("\nType in the words u wanna use:\n");
    for(int i = 0; i < size; i++) {
        printf("[%d]: ", i + 1);
        fgets(word[i], MAX_STR, stdin);
        CleanStr(word[i]);
    }

    printf("\nThese same words in alphabetical order:\n");
    AlphaOrder(word, size);
    printArray(word, size);

    for(int i = 0; i < size; i++) {
        free(word[i]);
    }
    free(word);

    return 0;
}

void AlphaOrder(char **var, int size) {
    char aux[MAX_STR];
    int replaces = 0;
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(strcoll(var[j], var[j + 1]) > 0) {
                strcpy(aux, var[j]);
                strcpy(var[j], var[j + 1]);
                strcpy(var[j + 1], aux);

                replaces = 1;
            }
        }
        if(!replaces) {
            printf("\nThere's no need for organization!\n");
            break;
        }
    }
}

void printArray(char **var, int size) {
    for(int i = 0; i < size; i++) {
        printf("%s\n", var[i]);
    }
}

void CleanIn() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void CleanStr(char var[]) {
    var[strcspn(var, "\n")] = '\0';
}