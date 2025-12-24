#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR (1ULL << 7)


size_t strsiz(const char *str);
void strconcat(char **dest, char *src) ;
void strcopy(char *dest, const char *src);
int strcomp(const char *str1, const char *str2);
void CleanStr(char *str, char target, char repl);

int main(void) {
    char *str1 = calloc(MAXCHAR, sizeof(char));
    char *str2 = calloc(MAXCHAR, sizeof(char));

    if (!str1 || !str2) {
        printf("Memory allocation error!\n!");
        return 1;
    }

    printf("Enter string n1: ");
    fgets(str1, MAXCHAR, stdin);
    CleanStr(str1, '\n', '\0');
    
    printf("Enter string n2: ");
    fgets(str2, MAXCHAR, stdin);
    CleanStr(str2, '\n', '\0');

    printf("\n\"%s\" + \"%s\" = ", str1, str2);
    strconcat(&str1, str2);
    printf("%s\n", str1);

    free(str1);
    free(str2);

    return 0;
}

void strconcat(char **dest, char *src) {
    size_t end = strsiz(*dest);
    size_t add = strsiz(src);

    *dest = realloc(*dest, end + add + 1);

    if (*dest == NULL) return;

    for (size_t i = 0; i < add; i++) {
        (*dest)[end + i] = src[i];
    }
    (*dest)[end + add] = '\0';
}

size_t strsiz(const char *str) {
    size_t i = 0;
    while (str[i]) i++;
    return i;
}

void strcopy(char *dest, const char *src) {
    dest = realloc(dest, strsiz(src));

    for (size_t i = 0; dest[i]; i++) 
        dest[i] = src[i];

    dest[strsiz(src)] = '\0';
}

void CleanStr(char *str, char target, char repl) {
    for (size_t i = 0; str[i]; i++) 
        if (str[i] == target) str[i] = repl;
}

int strcomp(const char *str1, const char *str2) {
    for (size_t i = 0; str2[i]; i++) 
        if (str1[i] != str2[i]) return 1;

    return 0;
}