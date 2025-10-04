#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...);

int main() {
    int x = 5, y = 5, z = 5;
    
    printf("%d", sum(3, x, y, z));
}

int sum(int count, ...) {
    va_list args;
    va_start(args, count);

    int result = 0;

    for(int i = 0; i < count; i++) {
        result += va_arg(args, int);
    }

    va_end(args);
    return result;
}