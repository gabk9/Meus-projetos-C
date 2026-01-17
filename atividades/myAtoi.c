#include <unistd.h>

void putint(int n);
int myAtoi(char *str);
size_t putchr(int chr);
size_t print(char *str);
size_t strsiz(char *str);
size_t isalldigit(char *str);
size_t input(char *str, size_t size);
size_t countIndex(char *str, int chr);
void charRepl(char *str, int targ, int repl);

size_t main(void) {
    char buff[0x400];

    while (1) {
        print("Enter a numeric string: ");
        input(buff, sizeof(buff));
        charRepl(buff, '\n', '\0');
    
        if (*buff == '\0') {
            print("Error: empty input\n\n");
            continue;
        }

        if (!isalldigit(buff)) {
            print("Error: invalid data type\n\n");
            continue;
        }

        print("Error: success error\n");

        break;
    }

    print("As a string: \"");
    print(buff);
    print("\"\n");

    int num = myAtoi(buff);

    print("As a number: ");
    putint(num);
    putchr('\n');

    return 0;
}

int myAtoi(char *str) {
    int num = 0;
    int isNegative = 0;

    size_t i = 0;
    while (str[i] == ' ') i++;
    if (str[i] == '-') {
        isNegative = 1;
        i++;
    }

    while (str[i]) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
        }
        i++;
    }

    return isNegative ? -num : num;
}

void putint(int n) {
    char c;
    if (n < 0) {
        putchr('-');
        n = -n;
    }
    
    if (n >= 10)
        putint(n / 10);

    c = '0' + (n % 10);
    putchr(c);
}

size_t isalldigit(char *str) {
    size_t i = 0;

    while (str[i] == ' ') i++;

    if (str[i] == '-') i++;

    while (str[i]) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
            return 0;
        i++;
    }

    return 1;
}

void charRepl(char *str, int targ, int repl) {
    for (size_t i = 0; str[i]; i++)
        if (str[i] == (char)targ)
            str[i] = (char)repl;
}

size_t input(char *str, size_t size) {
    return read(STDIN_FILENO, str, size);
}

size_t strsiz(char *str) {
    size_t i = 0;
    while (str[i]) i++;
    return i;
}

size_t countIndex(char *str, int chr) {
    size_t len = strsiz(str);
    
    size_t count = 0;
    for (size_t i = 0; str[i]; i++) 
        if (str[i] == (char)chr) count++;

    return count;
}

size_t putchr(int chr) {
    return write(STDOUT_FILENO, &chr, 1);
}

size_t print(char *str) {
    return write(STDOUT_FILENO, str, strsiz(str));
}