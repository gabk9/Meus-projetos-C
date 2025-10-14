#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR (1ULL << 6)

char *tolowerstr(const char *string);
char *tolowerstr2(const char *string);

int main(void) {
    char *str = calloc(MAXCHAR, sizeof(char));
    if (!str) {
        printf("Memory allocation error!!");
        return 1;
    }

    printf("Enter a string: ");
    fgets(str, MAXCHAR, stdin);
    str[strcspn(str, "\n")] = '\0';

    char *copy = tolowerstr(str);

    printf("\nOriginal string: \"%s\"\n", str);
    printf("The same string with only lowercase letters, without ctype.h: \"%s\"\n", copy);
    
    copy = tolowerstr2(str);
    printf("Now using ctype.h: \"%s\"\n", copy);

    free(str);

    return 0;
}

char *tolowerstr2(const char *string) {
    char *copy = malloc(strlen(string) + 1);
    if (!copy) return NULL;
    
    strcpy(copy, string);

    for (size_t i = 0; copy[i]; i++)
        copy[i] = (char)tolower((unsigned char)copy[i]);

    copy[strlen(string)] = '\0';
    return copy;
}

char *tolowerstr(const char *string) {
    char *copy = malloc(strlen(string) + 1);
    if (!copy) return NULL;
    
    strcpy(copy, string);

    const char lowerChars[] = "abcdefghijklmnopqrstuvwxyz";
    const char upperChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (size_t i = 0; copy[i]; i++)
        for (size_t j = 0; upperChars[j]; j++) 
            if (copy[i] == upperChars[j])
                copy[i] = lowerChars[j];
        
    return copy;
}