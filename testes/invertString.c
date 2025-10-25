#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 256

char *invertStr(char *str, size_t length);

int main() {
    char *word = calloc(MAX_CHAR, sizeof(char));
    
    printf("Enter a string: ");
    fgets(word, MAX_CHAR, stdin);
    word[strcspn(word, "\n")] = '\0';
    
    char *cpy = malloc(strlen(word) * sizeof(char));
    strcpy(cpy, word);
    char *newWord = malloc(strlen(word) * sizeof(char));
    strcpy(newWord, invertStr(word, strlen(word)));

    printf("\"%s\" inverted: \"%s\"\n", cpy, newWord);

    free(word);
    free(cpy);
    free(newWord);

    return 0;
}

char *invertStr(char *str, size_t length) {
    if(length <= 1) 
        return str;  

    char temp;
    for(int rsi = 0; rsi < length / 2; rsi++) {
        temp = str[rsi];
        str[rsi] = str[length - rsi - 1];
        str[length - rsi - 1] = temp;
    }
    return str;
}