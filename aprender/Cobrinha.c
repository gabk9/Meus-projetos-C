#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LARGURA 40
#define ALTURA 20
#define MAX_TAM 100

#define CIMA 1
#define BAIXO 2
#define ESQUERDA 3
#define DIREITA 4

typedef struct {
    int x, y;
} Ponto;

Ponto cobra[MAX_TAM];
int tamanho;
int direcao;
Ponto comida;

HANDLE hConsole;

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);
}

void setCor(int corTexto, int corFundo) {
    SetConsoleTextAttribute(hConsole, (corFundo << 4) | corTexto);
}

void desenharBordas() {
    setCor(7, 0);
    for (int x = 0; x <= LARGURA + 1; x++) {
        gotoxy(x, 0); printf("#");
        gotoxy(x, ALTURA + 1); printf("#");
    }
    for (int y = 1; y <= ALTURA; y++) {
        gotoxy(0, y); printf("#");
        gotoxy(LARGURA + 1, y); printf("#");
    }
}

void inicializarCobra() {
    tamanho = 5;
    direcao = DIREITA;
    int inicioX = LARGURA / 2;
    int inicioY = ALTURA / 2;
    for (int i = 0; i < tamanho; i++) {
        cobra[i].x = inicioX - i;
        cobra[i].y = inicioY;
    }
}

void desenharCobra() {
    for (int i = 0; i < tamanho; i++) {
        gotoxy(cobra[i].x + 1, cobra[i].y + 1);
        setCor(10, 0); // verde
        printf(i == 0 ? "@" : "O");
    }
}

void limparCauda() {
    gotoxy(cobra[tamanho - 1].x + 1, cobra[tamanho - 1].y + 1);
    printf(" ");
}

void moverCobra() {
    for (int i = tamanho - 1; i > 0; i--)
        cobra[i] = cobra[i - 1];

    switch (direcao) {
        case CIMA: cobra[0].y--; break;
        case BAIXO: cobra[0].y++; break;
        case ESQUERDA: cobra[0].x--; break;
        case DIREITA: cobra[0].x++; break;
    }
}

void gerarComida() {
    comida.x = rand() % LARGURA;
    comida.y = rand() % ALTURA;
}

void desenharComida() {
    gotoxy(comida.x + 1, comida.y + 1);
    setCor(12, 0); // vermelho
    printf("*");
}

int bateu() {
    if (cobra[0].x < 0 || cobra[0].x >= LARGURA || cobra[0].y < 0 || cobra[0].y >= ALTURA)
        return 1;
    for (int i = 1; i < tamanho; i++) {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y)
            return 1;
    }
    return 0;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': case 'W': if (direcao != BAIXO) direcao = CIMA; break;
            case 's': case 'S': if (direcao != CIMA) direcao = BAIXO; break;
            case 'a': case 'A': if (direcao != DIREITA) direcao = ESQUERDA; break;
            case 'd': case 'D': if (direcao != ESQUERDA) direcao = DIREITA; break;
        }
    }
}

int comeuComida() {
    return cobra[0].x == comida.x && cobra[0].y == comida.y;
}

void esconderCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int perguntarSeDesejaTentarNovamente() {
    char resposta;
    gotoxy(LARGURA / 2 - 10, ALTURA / 2 + 1);
    setCor(7, 0);
    printf("Deseja tentar novamente? (S/N): ");
    do {
        resposta = _getch();
        resposta = toupper(resposta);
    } while (resposta != 'S' && resposta != 'N');

    return (resposta == 'S');
}

void jogar() {
    system("cls");
    inicializarCobra();
    desenharBordas();
    gerarComida();

    while (1) {
        limparCauda();
        moverCobra();

        if (bateu()) {
            setCor(12, 0);
            gotoxy(LARGURA / 2 - 5, ALTURA / 2);
            printf(" GAME OVER ");
            break;
        }

        if (comeuComida()) {
            if (tamanho < MAX_TAM) tamanho++;
            gerarComida();
        }

        desenharComida();
        desenharCobra();
        input();
        Sleep(100);
    }
}

int main() {
    srand(time(NULL));
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    esconderCursor();

    do {
        jogar();
    } while (perguntarSeDesejaTentarNovamente());

    setCor(7, 0);
    gotoxy(0, ALTURA + 3);
    return 0;
}
