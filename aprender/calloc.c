#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    char *x; 
    
    //x = malloc(sizeof(char)); 
    x = calloc(1, sizeof(char)); // alocando 1 byte (char) para um elemento que neste caso � char
    
    if(x) {
        printf("Mem�ria alocada com Sucesso!\n");
        printf("X = %c\n", *x);
        *x = 'G';
        printf("X = %c", *x);
    }else {
        printf("Erro na aloca��o de mem�ria!");
    }


    return 0;
}