#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *invertStr(char *str, size_t length);

#define MAX_CHAR 50

int main() {
    char *word = calloc(MAX_CHAR, sizeof(char));
    
    printf("Enter a string: ");
    fgets(word, MAX_CHAR, stdin);
    word[strcspn(word, "\n")] = '\0';
    
    int len = strlen(word);
    char *copy = calloc(len, sizeof(char));
    char *newWord = calloc(len, sizeof(char));
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