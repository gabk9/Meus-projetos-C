#include <locale.h>
#include <stdio.h>
#include "MyIo.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    int idade;
    printf("Me diga sua idade: ");
    readInt(&idade, 12); // vermelho claro para erro
    printf("Sua idade é: %d\n", idade);

    return 0;
}
