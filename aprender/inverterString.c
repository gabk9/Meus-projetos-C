#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ReverseStr(char var[]);
char *ReversePstr(const char var[]);

int main() {
    char copy[100], *word;

    printf("Type-in a text: ");
    fgets(copy, sizeof(copy), stdin);
    copy[strcspn(copy, "\n")] = '\0';

    printf("%s\n\n", copy);
    ReverseStr(copy);
    printf("%s", copy);

    printf("\nString inverted with pointers:\n");
    word = ReversePstr(copy);

    printf("%s\n", word);

    free(word);

    return 0;
}

void ReverseStr(char var[]) {
    int len = strlen(var), end, i, aux;

    end = len - 1; 
    for(i = 0; i < len/2; i++){
        aux = var[i];
        var[i] = var[end];
        var[end] = aux;
        end--;
    }
}

char *ReversePstr(const char var[]) {
    int len = strlen(var), end, i, aux;
    char *new = calloc((len + 1), sizeof(char));

    end = len - 1; 
    for(i = 0; i < len; i++){
        new[end] = var[i];
        end--;
    }
    new[i] = '\0';
    return new;
}