#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int *x; 
    
    x = malloc(sizeof(int)); // Aloca 4 bytes, int tem 4 bytes
    
    if(x) {
        printf("Mem�ria alocada com Sucesso!\n");
        printf("X = %d\n", *x);
        *x = 50;
        printf("X = %d", *x);
    }else {
        printf("Erro na aloca��o de mem�ria!");
    }


    return 0;
}