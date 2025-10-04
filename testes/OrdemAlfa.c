#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 50

void CleanStr(char *var);
int AlphaOrder(char **array, int size) ;
void printA(char **array, int size);
void CleanIn();
int switches = 0;

int main(int argc, char **argv) {
    char **word, *buff = (char *)calloc(MAXSTR, sizeof(char));
    int qtd;

    if(!buff) {
        printf("\nError during allocation!!\n");
        return 1;
    }

    do {
        memset(buff, 0, MAXSTR);
        printf("How many words do you wish to use? ");
        fgets(buff, MAXSTR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &qtd) != 1) {
            printf("\nError!!, wrong type of data\n\n");
            continue;
        }

        if(qtd <= 0) {
            printf("\nPlease, choose a number greater than 0!\n\n");
        }

    } while (qtd <= 0);

    free(buff);

    word = (char **)calloc(qtd, sizeof(char *));
    
    if(!word) {
        printf("\nError during allocation!!\n");
        return 1;
    }

    for(size_t j = 0; j < qtd; j++) {
        word[j] = (char *)calloc(MAXSTR, sizeof(char));
        if(!word[j]) {
            printf("\nError during array allocation!!\n");
            return 1;
        }
    }

    for(size_t i = 0; i < qtd; i++) {
        printf("\nType-in the word n%zu: ", i + 1);
        fgets(word[i], MAXSTR, stdin);
        CleanStr(word[i]);
    }
    
    if (AlphaOrder(word, qtd)) {
        printf("\nThe array you just typed organized in alphabetical order:\n");
        printA(word, qtd);
    }

    for(size_t k = 0; k < qtd; k++) {
        free(word[k]);
    }
    free(word);

    return 0;
}

int AlphaOrder(char **array, int size) {
    char *aux;
    switches = 0;

    for(size_t i = 0; i < size - 1; i++) {
        for(size_t j = 0; j < size - i - 1; j++) {
            if(strcasecmp(array[j], array[j + 1]) > 0) {
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;

                switches = 1;
            }
        }
        if(!switches) {
            printf("\nThere's no need to organize the array!!\n");
            break;
        }
    }
    return 1;
}

void printA(char **array, int size) {
    for(size_t i = 0; i < size; i++) {
        printf("%s\n", array[i]);
    }
}

void CleanStr(char *var) {
    var[strcspn(var, "\n")] = '\0';
}