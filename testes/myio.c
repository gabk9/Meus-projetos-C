#include <unistd.h>

size_t strsiz(const char *str);
ssize_t myPrintf(const char *in);
void CleanStr(char *str, char targ, char repl);
size_t strcomp(const char *str1, const char *str2);
ssize_t myScanf(size_t bytes, const char *fmt, void *out);

int main(void) {
    char str[64];
    char letter;

    myPrintf("Enter a string: ");
    myScanf(sizeof(str), "%s", str);
    CleanStr(str, '\n', '\0');

    myPrintf("The string you just entered: ");
    myPrintf(str);


    myPrintf("\n\nEnter a char: ");
    myScanf(1, "%c", &letter);
    CleanStr(&letter, '\n', '\0');
    
    char buff[2] = {letter, '\0'};
    myPrintf("The char you just entered: ");
    myPrintf(buff);

    return 0;
}

ssize_t myScanf(size_t bytes, const char *fmt, void *out) {
    ssize_t len = -1;
    if (strcomp(fmt, "%s") == 0) {
        len = read(0, out, bytes - 1);
        if (len > 0) {
            ((char*)out)[len] = '\0';
            CleanStr((char *)out, '\n', '\0');
        } else
            len = -1;
    } else if (strcomp(fmt, "%c") == 0) {
        len = read(0, out, bytes);
        
        if (len != 1)
            len = -1;

    }

    return len;
}

void CleanStr(char *str, char targ, char repl) {
    for (size_t i = 0; str[i]; i++)
        if (str[i] == targ) str[i] = repl;
}

size_t strcomp(const char *str1, const char *str2) {
    for (size_t i = 0; str2[i]; i++) 
        if (str1[i] != str2[i]) return 1;
    return 0;
}

ssize_t myPrintf(const char *in) {
    ssize_t len = write(1, in, strsiz(in));
    return len;
}

size_t strsiz(const char *str) {
    size_t i = 0;
    while (str[i]) i++;
    return i;
}
