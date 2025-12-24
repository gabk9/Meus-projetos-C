#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 64
#define OPERATIONS "+-/*^%%"

void trim(char *str);
void trimEnd(char *str);
size_t findFloatDigits(double n);
double calc(double num1, char operation, double num2);

int main(void) {
    char *string = calloc(MAXCHAR, 1);
    double n1 = 0, n2 = 0, result = 0;

    while (1) {
        printf("Enter mathematic expression: ");
        fgets(string, MAXCHAR, stdin);
        string[strcspn(string, "\n")] = '\0';
    
        if (strcmp(string, "quit") == 0)
            break;

        char op = 0;
        size_t op_pos = 0;

        for (size_t i = 1; string[i]; i++) {
            if (strchr(OPERATIONS, string[i])) {
                op = string[i];
                op_pos = i;
                break;
            }
        }

        if (!op) {
            puts("Invalid expression (no operator).");
            continue;
        }

        char *num1 = string;
        char *num2 = string + op_pos + 1;
        string[op_pos] = '\0';

        trim(num1);
        trim(num2);
        trimEnd(num1);
        trimEnd(num2);

        if (!*num1) {
            puts("Missing first operand.");
            continue;
        }
        if (!*num2) {
            puts("Missing second operand.");
            continue;
        }

        n1 = atof(num1);
        n2 = atof(num2);
        result = calc(n1, op, n2);

        int fp1 = findFloatDigits(n1);
        int fp2 = findFloatDigits(n2);
        int fp3 = findFloatDigits(result);

        printf("%g %c %g = %g\n\n", n1, op, n2, result);
    }

    free(string);
    return 0;
}

size_t findFloatDigits(double n) {
    char *buff = calloc(MAXCHAR, 1);
    snprintf(buff, MAXCHAR, "%.15lg", n);

    char *dot = strchr(buff, '.');
    if (!dot) {
        free(buff);
        return 0;
    }

    char *floatingPart = dot + 1;
    int end = strlen(floatingPart);

    while (end > 0 && floatingPart[end - 1] == '0')
        end--;

    floatingPart[end] = '\0';

    size_t digits = strlen(floatingPart);
    free(buff);
    return digits;
}
double calc(double num1, char operation, double num2) {
    switch (operation) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '^': return powf(num1, num2);
        case '%': return (int)num1 % (int)num2; break;
        default: return 0;
    }
}

void trimEnd(char *str) {
    size_t len = strlen(str);
    for (int i = (int)len - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            str[i + 1] = '\0';
            break;
        }
    }
}

void trim(char *str) {
    if (str == NULL) return;
    size_t spaces = 0;
    while (str[spaces] == ' ') spaces++;
    if (spaces == 0) return;

    size_t i = 0;
    while (str[spaces + i] != '\0') {
        str[i] = str[spaces + i];
        i++;
    }
    str[i] = '\0';
}
