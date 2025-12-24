#include <stdio.h>
#include <locale.h>

void bubbleSort(int array[], int tamanho);
int buscaBinaria(int array[], int tamanho, int alvo);
void printArray(int array[], int tamanho);

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int vetor[] = {7, 3, 9, 1, 6, 2, 8, 5, 4, 10};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int numero, posicao;

    bubbleSort(vetor, tamanho);
    printf("Vetor ordenado: ");
    printArray(vetor, tamanho);

    printf("Digite o numero que deseja buscar: ");
    scanf("%d", &numero);

    posicao = buscaBinaria(vetor, tamanho, numero);

    if (posicao != -1) {
        printf("Numero %d encontrado na posição %d do vetor ordenado.\n", numero, posicao);
    } else {
        printf("Numero %d nao encontrado no vetor.\n", numero);
    }

    return 0;
}

void bubbleSort(int array[], int tamanho) {
    int trocou;
    for (int i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                trocou = 1;
            }
        }
        if (trocou == 0) {
            break;
        }
    }
}

int buscaBinaria(int array[], int tamanho, int alvo) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (array[meio] == alvo) {
            return meio;
        } else if (array[meio] < alvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

void printArray(int array[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
