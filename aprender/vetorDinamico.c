#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    int i, *vet, tam;

    printf("Digite o tamanho desse vetor: ");
    scanf("%d", &tam);
    srand(time(NULL));  
    
    vet = malloc(tam * sizeof(int)); // 4 bytes para a quantidade "tam" de inteiros
    // vet = calloc(tam, sizeof(int));
    
    if(vet) {
        printf("Alocado com sucesso!\n");
        for(i = 0; i < tam; i++) {
            vet[i] = rand() % 100; // *(vet + i) = rand() % 100;
        }for(i = 0; i < tam; i++){  
            printf("%d ", vet[i]); // printf("%d ", *(vet + i));
        }
        printf("\n\n");

        printf("Digite o novo tamanho do vetor: ");
        scanf("%d", &tam);

        vet = realloc(vet, tam); // Aloca um novo tamanho ao ponteiro "vet"

        printf("Vetor realocado:\n");
        for(i = 0; i < tam; i++){  
            printf("%d ", vet[i]); // printf("%d ", *(vet + i));
        }
        printf("\n\n");

        free(vet);

    }else {
        printf("Erro ao alocar mem�ria!\n");
    }

    return 0;
}