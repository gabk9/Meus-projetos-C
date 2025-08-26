#include "MyIo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

static HANDLE hConsole = NULL;

void readInt(int *out, int errorColor) {
    if (!hConsole)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char buffer[100];
    int valor;
    char *endptr;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            SetConsoleTextAttribute(hConsole, errorColor);
            printf("Erro ao ler entrada. Tente novamente.\n");
            SetConsoleTextAttribute(hConsole, 7);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char *start = buffer;
        while (isspace(*start)) start++;

        valor = (int)strtol(start, &endptr, 10);

        while (isspace(*endptr)) endptr++;

        if (*start != '\0' && *endptr == '\0') {
            *out = valor;
            return;
        }

        SetConsoleTextAttribute(hConsole, errorColor);
        printf("Valor inválido! Digite um número inteiro válido.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
}

void readChar(char *out, int errorColor) {
    if (!hConsole)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char buffer[100];

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        char *start = buffer;
        while (*start && isspace(*start)) start++;

        if (start[0] != '\0' && start[1] == '\0' && (unsigned char)start[0] >= 32 && (unsigned char)start[0] <= 126) {
            *out = start[0];
            return;
        }

        SetConsoleTextAttribute(hConsole, errorColor);
        printf("Caractere inválido! Digite um caractere ASCII normal.\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
}

void readString(char *out, int maxLen, int errorColor) {
    if (!hConsole)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char buffer[1024];

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        char *start = buffer;
        while (*start && isspace(*start)) start++;

        if (*start != '\0' && strlen(start) < maxLen) {
            strncpy(out, start, maxLen - 1);
            out[maxLen - 1] = '\0';
            return;
        }

        SetConsoleTextAttribute(hConsole, errorColor);
        printf("Texto inválido!\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
}

void readFloat(float *out, int errorColor) {
    if (!hConsole)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char buffer[100];
    char *endptr;
    float valor;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            SetConsoleTextAttribute(hConsole, errorColor);
            printf("Erro na leitura!\n");
            SetConsoleTextAttribute(hConsole, 7);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char *start = buffer;
        while (isspace(*start)) start++;

        valor = strtof(start, &endptr);

        while (isspace(*endptr)) endptr++;

        if (*start != '\0' && *endptr == '\0') {
            *out = valor;
            return;
        }

        SetConsoleTextAttribute(hConsole, errorColor);
        printf("Valor inválido!\n");
        SetConsoleTextAttribute(hConsole, 7);
    }
}

void cleanInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}