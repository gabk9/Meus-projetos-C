#include <stdio.h>
#include <ctype.h>

int main() {
    char word[50];

    printf("Type-in a phrase: ");
    fgets(word, sizeof(word), stdin);

    for(int i = 0; word[i] != '\0'; i++) {
        if(isdigit(word[i]) == 1) {
            putchar(word[i]);
        }
    }

    return 0;
}