#include <stdio.h>

int main() {
    int lista[10] = {1, 2, 3};
    int tam = 0;
    int novo;

    while(lista[tam] != 0 && tam < 10) tam++;

    printf("Original list:\n");
    for (int i = 0; i < tam; i++) printf("%d ", lista[i]);

    printf("\n\nType-in a number to add on the list: ");
    scanf("%d", &novo);

    lista[tam] = novo;
    tam++;

    printf("\nUpdated list:\n");
    for (int i = 0; i < tam; i++) printf("%d ", lista[i]);

    return 0;
}
