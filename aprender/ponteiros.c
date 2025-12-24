#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no{
    int valor;
    struct no *proximo;     
} No;


void Extremos(int *v, int *min, int *max, int size);
void printLista(No *inicio);
void Inserir2(No **inicio, int x);
No* Inserir(No* inicio, int x);


int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int valor = 10, menor, maior, vet[] = {50, 10, 100, 200, 150, 245};
    int *p = &valor;
    No *lista = NULL;

    printf("Valor: %d\t%p \n", valor, p);

    Extremos(vet, &menor, &maior, 6);
    printf("No main: Menor: %d\tMaior: %d\n", menor, maior);

    lista = Inserir(lista, 10);
    lista = Inserir(lista, 50);
    lista = Inserir(lista, 100);
    
    printf("\n");

    Inserir2(&lista, 17);
    Inserir2(&lista, 57);
    Inserir2(&lista, 107);

    printLista(lista);

    return 0;
}

No* Inserir(No* inicio, int x) {
    No *novo = malloc(sizeof(No));//ponteiro de struct
    if(novo) {
        novo->valor = x; // (*novo).valor = x;
        novo->proximo = inicio; // (*novo).proximo = inicio;
    }
    return novo;
}

void Inserir2(No **inicio, int x) {
    No *novo = malloc(sizeof(No));//ponteiro de struct
    if(novo) {
        novo->valor = x; // (*novo).valor = x;
        novo->proximo = *inicio; // (*novo).proximo = *inicio;
        *inicio = novo;
    }

}

void printLista(No *inicio) {
    if(inicio) {
        printf("%d ", inicio->valor);
        printLista(inicio->proximo); // Função recursiva
    }
}

void Extremos(int *v, int *min, int *max, int size) {
    int i;
    *min = v[0];
    *max = v[0];
    for(i = 1; i < size; i++) {
        if(v[i] < *min) {
            *min = v[i];
        }
        if(v[i] > *max) {
            *max = v[i];
        }
    }
    printf("Na função: Menor: %d\tMaior: %d\n", *min, *max);
}