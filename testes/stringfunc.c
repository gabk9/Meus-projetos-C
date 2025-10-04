#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CHAR 100

void trim(char *str);
void trim2(char *str);
void CleanStr(char *str);

int main() {
    char *string = calloc(MAX_CHAR, sizeof(char));
    
    printf("Type-in a string: ");
    fgets(string, MAX_CHAR, stdin);
    CleanStr(string);
    
    char *token = strtok(string, ",");
    int i = strcspn(string, ",");

    if(string[i] != '\0') {
        printf("%c was found in %s\n", (char)string[i], string);
    }

    printf("\nYour string organized into a list:\n");
    int count = 0;
    while(token != NULL) {
        trim(token);
        count++;
        printf("[%d] %s\n", count, token);
        token = strtok(NULL, ",");
    }

    free(string);

    return 0;
}

void trim2(char *str) {
    int start = 0;
    while(str[start] && isspace(str[start])) start++;

    int end = strlen(str) - 1;
    while(end >= start && isspace(str[end])) end--;

    int j = 0;
    for(int i = start; i <= end; i++) {
        str[j++] = str[i];
    }
    str[j] = '\0';
}


void trim(char *str) {
    char *start = str;
    while(*start == ' ') start++;

    if(start != str) {
        char *dst = str;
        while(*start) {
            *dst++ = *start++;
        }
        *dst = '\0';
    }

    char *end = str + strlen(str) - 1;
    while(end > str && *end == ' ') {
        *end = '\0';
        end --;
    }
}

void CleanStr(char *str) {
    str[strcspn(str, "\n")] = '\0';
}