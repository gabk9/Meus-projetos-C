#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios old, new;

    tcgetattr(STDIN_FILENO, &old);
    new = old;

    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    printf("Pressione teclas (q para sair)\n");
    fflush(stdout);

    while (1) {
        char buf[8];
        int n = read(STDIN_FILENO, buf, sizeof(buf));

        if (n == 1) {
            char c = buf[0];

            if (c == 'q') break;

            if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
            } else {
                putchar(c);
                fflush(stdout);
            }
        }
        else if (n == 3 && buf[0] == 27 && buf[1] == '[') {
            switch (buf[2]) {
                case 'A': printf("\n[SETA CIMA]\n"); break;
                case 'B': printf("\n[SETA BAIXO]\n"); break;
                case 'C': printf("\n[SETA DIREITA]\n"); break;
                case 'D': printf("\n[SETA ESQUERDA]\n"); break;
            }
            fflush(stdout);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return 0;
}
