#include <stdio.h>
#include <unistd.h>

void loading(int ms);
void Vload(int ms);

int main() {
    loading(25);
    printf("\n");
    Vload(25);
    return 0;
}

void loading(int ms) {
    for (int i = 0; i <= 100; i++) {
        printf("\r\033[2K");
        printf("\r[%3d%%]", i);
        fflush(stdout);
        usleep(ms * 1000);
    }
}

void Vload(int ms) {
    int total = 30;
    for(int i = 0; i <= total; i++) {
        int percent = (i * 100) / total;
        printf("\r[");

        for(int j = 0; j < i; j++) {
            printf("#");
        }

        for(int k = i; k < total; k++) {
            printf(" ");
        }

        printf("] %3d%%", percent);
        fflush(stdout);
        usleep(ms * 1000);
    }
    printf("\n");
}