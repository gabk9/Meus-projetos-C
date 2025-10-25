#include <stdio.h>

int main() {
    unsigned char a = 5;  // 00000101
    unsigned char b = 9;  // 00001001
    int c = 5, d = 6;

    printf("a = %d, b = %d\n\n", a, b);
    printf("a & b = %d\n", a & b);    // 00000001 = 1
    printf("a | b = %d\n", a | b);    // 00001101 = 13
    printf("a ^ b = %d\n", a ^ b);    // 00001100 = 12
    printf("~a = %d\n", ~a);          // 11111010 = -6 (em 2's complemento)
    printf("b << 1 = %d\n", b << 1);  // 00010010 = 18
    printf("b >> 1 = %d\n", b >> 1);  // 00000100 = 4

    (c & 1) ? printf("\n\n\"c\" Impar") : printf("\n\n\"c\" Par");
    (d & 1) ? printf("\n\n\"d\" Impar") : printf("\n\n\"d\" Par");

    return 0;
}
