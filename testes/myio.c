#include <unistd.h>

#ifdef _WIN32
    #error "This code only works on linux and mac"
    #error "Stopping compilation."
#endif

size_t strsiz(const char *str);
ssize_t myPrintf(const void *in, size_t bytes);
size_t strcomp(const char *str1, const char *str2);
ssize_t myScanf(size_t bytes, const char *fmt, void *out);

int main(void) {
    char str[64];
    char letter;

    myPrintf("Enter a string: ", 16);
    myScanf(sizeof(str), "%s", str);

    myPrintf("The string you just entered: ", 29);
    myPrintf(str, strsiz(str));


    myPrintf("\nEnter an char: ", 16);
    myScanf(1, "%c", &letter);

    myPrintf("The char you just entered: ", 27);
    myPrintf(&letter, 1);

    return 0;
}

ssize_t myScanf(size_t bytes, const char *fmt, void *out) {
    ssize_t len = -1;
    if (strcomp(fmt, "%s") == 0) {
        len = read(0, out, bytes - 1);
        if (len > 0)
            ((char*)out)[len] = '\0';
        else
            len = -1;

    } else if (strcomp(fmt, "%c") == 0) {
        len = read(0, out, bytes);
        
        if (len != 1)
            len = -1;
    }
    return len;
}

size_t strcomp(const char *str1, const char *str2) {
    for (size_t i = 0; str2[i]; i++) 
        if (str1[i] != str2[i]) return 1;
    return 0;
}

ssize_t myPrintf(const void *in, size_t bytes) {
    ssize_t len = write(1, in, bytes);
    return len;
}

size_t strsiz(const char *str) {
    size_t i = 0;
    while (str[i]) i++;
    return i;
}