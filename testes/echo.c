#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        write(1, argv[i], strlen(argv[i]));
        if (i < argc - 1) write(1, " ", 1);
    }
    write(1, "\n", 1);

    char buffer[64];
    int n = read(0, buffer, 50);
    if (n > 0) {
        buffer[n] = '\0';
        write(1, buffer, n);
        write(1, "\n", 1);
    }

    return 0;
}
