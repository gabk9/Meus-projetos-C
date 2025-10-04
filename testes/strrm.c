#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR (1ULL << 6)


size_t strsiz(const char *str);
char *strcopy(char *src);
char *strrem(char *str, const char *substr);
void CleanStr(char *str, char target, char repl);

int main(void) {
    char *string1 = calloc(MAXCHAR, sizeof(char));
    char *string2 = calloc(MAXCHAR, sizeof(char));

    printf("Enter the 1-st string: ");
    fgets(string1, MAXCHAR, stdin);
    CleanStr(string1, '\n', '\0');
    
    printf("Enter the 2-nd string: ");
    fgets(string2, MAXCHAR, stdin);
    CleanStr(string2, '\n', '\0');

    char *new = strcopy(strrem(string1, string2));

    printf("\n%s", new);

    return 0;
}

char *strrem(char *str, const char *substr) {
    int len = strsiz(str);
    int sublen = strsiz(substr);
    char *copy = strcopy(str);


    if (sublen == 0 || len < sublen)
        return copy;

    for (size_t i = 0; i <= len - sublen; i++) {
        int match = 1;
        for (size_t j = 0; j < sublen; j++) {
            if (copy[i + j] != substr[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            for (size_t k = i; k <= len - sublen; k++) 
                copy[k] = copy[k + sublen];
            break;
        }
    }

    return copy;
}

char *strcopy(char *src) {
    int len = strsiz(src);
    char *dest = malloc((len + 1) * sizeof(char));

    for (int i = 0; i <= len; i++) {
        dest[i] = src[i];
    }
    return dest;
}

void CleanStr(char *str, char target, char repl) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == target) 
            str[i] = repl;
    }
}

size_t strsiz(const char *str) {
    int i = 0;
    while (str[i]) i++;
    return i;
}