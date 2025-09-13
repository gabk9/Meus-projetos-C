#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 256

char *invertStr(char *str, size_t length);

int main(int argc, char **argv) {
    char *word = calloc(MAX_CHAR, sizeof(char));

    printf("Enter a string: ");
    fgets(word, MAX_CHAR, stdin);
    word[strcspn(word, "\n")] = '\0';

    char *cpy = malloc(strlen(word) * sizeof(char));
    strcpy(cpy, word);
    char *reversed = malloc(strlen(word) * sizeof(char));
    strcpy(reversed, invertStr(word, strlen(word)));

    char *Cmp = (strcasecmp(cpy, reversed) == 0) ? "is" : "isn't";

    printf("The word: \"%s\" %s a palindrome\n", cpy, Cmp);

    free(word);
    free(cpy);
    free(reversed);

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