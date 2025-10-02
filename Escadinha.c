#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void randCor(HANDLE hConsole, int min, int max);
void setCor(HANDLE hConsole, int cor);

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    srand(time(NULL));
    int h;

    printf("Me diga uma ");
    setCor(hConsole, 2); // Verde
    printf("altura");
    setCor(hConsole, 7); // Branco padrão
    printf(": ");
    scanf("%d", &h);

    system("cls");
    setCor(hConsole, 2);
    printf("Altura ");
    setCor(hConsole, 7);
    printf("igual a %d\n\n", h);

    for (int l = 0; l < h; l++) {
        setCor(hConsole, 7); // Fundo/texto padrão antes dos espaços
        for (int e = 0; e < h - l - 1; e++) {
            printf(" ");
        }

        // Escada esquerda
        for (int i = 0; i <= l; i++) {
            randCor(hConsole, 1, 15);
            printf("#");
        }
		
		setCor(hConsole, 7);
        printf("  ");

        // Escada direita
        for (int a = 0; a <= l; a++) {
            randCor(hConsole, 1, 15);
            printf("#");
        }

        // Limpar o restante da linha com fundo preto e texto branco
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int largura = csbi.dwSize.X;

        int usados = (h - l - 1) + (l + 1) + 2 + (l + 1);

        // Texto branco (7), fundo preto (0)
        SetConsoleTextAttribute(hConsole, (0 << 4) | 7);
        for (int i = usados; i < largura; i++) {
            printf(" ");
        }

        printf("\n");
    }

    setCor(hConsole, 7); // Reset geral
    return 0;
}

void randCor(HANDLE hConsole, int min, int max) {
    int cor = rand() % (max - min + 1) + min;
    SetConsoleTextAttribute(hConsole, (cor << 4) | cor); // Fundo e texto coloridos
}

void setCor(HANDLE hConsole, int cor) {
    SetConsoleTextAttribute(hConsole, cor); // Só cor do texto (ou padrão 7)
}
