#include <unistd.h>

#define MAXCHAR 0x100

void format(char *str);
int print(const char *str);
int strsiz(const char *str);
int input(char *str, int size);
void charReplace(char *str, int targ, int repl);

int main(void) {
    char str[MAXCHAR];
    
    print("Enter a string to format: ");
    input(str, MAXCHAR);
    charReplace(str, '\n', '\0');

    format(str);

    print("String formatted: '");
    print(str);
    print("'");
    
    return 0;
}

void charReplace(char *str, int targ, int repl) {
    for (int i = 0; str[i]; i++)
        if (str[i] == (char)targ) str[i] = (char)repl;
}

void format(char *str) {
    int r = 0;
    int w = 0;
    int last_space = 1;

    while (str[r]) {
        unsigned char c = str[r++];

        if (c & 0x80)
            continue;

        if (c >= 'A' && c <= 'Z')
            c = c + ('a' - 'A');

        if (c >= 'a' && c <= 'z') { 
            str[w++] = c;
            last_space = 0;
            continue;
        }

        if (c == ' ' && !last_space) {
            str[w++] = ' ';
            last_space = 1;
        }
    }

    if (w > 0 && str[w - 1] == ' ')
        w--;

    str[w] = '\0';
}

int input(char *str, int size) {
    return read(0, str, size);
}

int strsiz(const char *str) {
    int i = 0;
    while (str[i]) i++;
    return i;
}

int print(const char *str) {
    return write(1, str, strsiz(str));
}