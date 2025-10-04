#include <stdio.h>
#include <windows.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    const char *dia[] = {"\rSaindo...", "Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado"};
    int n;

    do{
    printf("Me diga um número de 1 a 7: ");
    scanf("%d", &n);

    (n >= 0 && n <= 7) ? printf("Dia: %s\n", dia[n]) : printf("Valor Inválido!\n");
    system("pause");
    system("cls");

    } while (n != 0);

    return 0;
}