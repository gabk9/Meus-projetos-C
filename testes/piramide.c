#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define SleepMs(ms) Sleep(ms)
    #define Clear() system("cls")
#else 
    #include <unistd.h>
    #define SleepMs(ms) usleep((ms) * 1000) 
    #define Clear() system("clear")
#endif

int main() {
    #ifdef __WIN32
        printf("Running on Windows!!\n\n");
    #else 
        printf("Running on Linux!!\n\n");
    #endif

    int h; 
    float b = 0;
    
    printf("Type-in the height: ");
    scanf("%d", &h);
    b = (2 * h) - 1;

    Clear();

    printf("A pyramid with the height of: %d\n", h);
    for(int x = 0; x < h; x++) {
        int Nhashes = (2 * x) + 1;
        int Nspaces = (b - Nhashes) / 2;

        for(int y = 0; y < Nspaces; y++) {
            printf(" ");
        }

        for(int z = 0 ; z < Nhashes; z++) {
            printf("#");
        }
        printf("\n");

    }

    return 0;
}