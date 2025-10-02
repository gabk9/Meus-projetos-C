#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    char *x; 
    
    //x = malloc(sizeof(char)); 
    x = calloc(1, sizeof(char)); // alocando 1 byte (char) para um elemento que neste caso é char
    
    if(x) {
        printf("Memória alocada com Sucesso!\n");
        printf("X = %c\n", *x);
        *x = 'G';
        printf("X = %c", *x);
    }else {
        printf("Erro na alocação de memória!");
    }


    return 0;
}