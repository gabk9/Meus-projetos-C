#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <locale.h>

bool ehPrimo(int n);
void listarPrimos();
void verificarPrimo();

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int opcao;
    do {
        printf("\n=== Calculadora de N�meros Primos ===\n");
        printf("1. Verificar se um n�mero � primo\n");
        printf("2. Listar todos os primos at� um n�mero\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                verificarPrimo();
                break;
            case 2:
                listarPrimos();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

bool ehPrimo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void verificarPrimo() {
    int num;
    printf("Digite um n�mero para verificar se � primo: ");
    scanf("%d", &num);
    if (ehPrimo(num)) {
        printf("%d � um n�mero primo.\n", num);
        system("pause");
        system("cls");
    } else {
        printf("%d N�O � um n�mero primo.\n", num);
        system("pause");
        system("cls");
    }
}

void listarPrimos() {
    int limite;
    printf("Listar primos at�: ");
    scanf("%d", &limite);
    printf("N�meros primos at� %d:\n", limite);
    for (int i = 2; i <= limite; i++) {
        if (ehPrimo(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    system("pause");
    system("cls");
}