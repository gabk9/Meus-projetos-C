#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define SleepMS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SleepMS(ms) usleep((ms) * 1000)
#endif

void loading(int ms, int lc);

int main() {
    
    loading(75, 50);

    return 0;
}

void loading(int ms, int lc) {
    char *ASCII[] = {"\r\\", "\r|", "\r/", "\r-"};
    int len = sizeof(ASCII) / sizeof(ASCII[0]);
    for(int i = 0; i < lc; i++) {
        for(int j = 0; j < len; j++) {
            printf("%s", ASCII[j]);
            fflush(stdout);
            SleepMS(ms);
        }
    }
}