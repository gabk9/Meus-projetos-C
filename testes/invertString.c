#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *invertStr(char *str, size_t length);

#define MAX_CHAR 256

int main() {
    char *word = calloc(MAX_CHAR, sizeof(char));
    
    printf("Enter a string: ");
    fgets(word, MAX_CHAR, stdin);
    word[strcspn(word, "\n")] = '\0';
    
    char *copy = malloc(strlen(word) * sizeof(char));
    char *newWord = malloc(strlen(word) * sizeof(char));
    strcpy(copy, word);
    strcpy(newWord, invertStr(word, strlen(word)));

    printf("\"%s\" inverted: \"%s\"\n", copy, newWord);

    free(word);
    free(newWord);
    return 0;
}

char *invertStr(char *str, size_t length) {
    if(length <= 1) 
        return str;  

    char temp;
    for(int i = 0; i < length / 2; i++) {
        temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
    return str;
}