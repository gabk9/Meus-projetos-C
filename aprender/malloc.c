#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int *x; 
    
    x = malloc(sizeof(int)); // Aloca 4 bytes, int tem 4 bytes
    
    if(x) {
        printf("Memória alocada com Sucesso!\n");
        printf("X = %d\n", *x);
        *x = 50;
        printf("X = %d", *x);
    }else {
        printf("Erro na alocação de memória!");
    }


    return 0;
}