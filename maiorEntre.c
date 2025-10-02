#include <stdio.h>

int main() {
    int qtd;

    printf("Me diga quantos numeros ira usar: ");
    scanf("%d", &qtd);

    int v[5], maior, menor;

    for(int i = 0; i < qtd; i++) {
        printf("Me diga um numero: ");
        scanf("%d", &v[i]);
    }

    menor = v[0];
    maior = v[0];

    for(int i = 1 ; i < qtd; i++) {
        if(v[i] > maior) maior = v[i];
        if(v[i] < menor) menor = v[i];
    }

    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);

    return 0;
}   