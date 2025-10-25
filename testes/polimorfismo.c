#include <stdio.h>

typedef struct {
    enum { T_INT, T_FLOAT, T_STRING } tipo;
    union {
        int i;
        float f;
        char s[20];
    } valor;
} Variavel;

int main() {
    Variavel v;

    v.tipo = T_STRING;
    snprintf(v.valor.s, sizeof(v.valor.s), "Gabriel");

    if (v.tipo == T_STRING)
        printf("String: %s\n", v.valor.s);

    return 0;
}
