#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXCHAR (1ULL << 8)

void CleanIn(void);
void toBinary64(uint64_t n);
uint64_t bintoint64(const char *bin);

typedef enum {
    EXIT, DECIMAL, HEX, BINARY, OCT
} fmt;

int main(void) {
    uint64_t n = 0;
    char *binary = calloc(MAXCHAR, sizeof(char));
    int op;

    printf("[1] Enter decimal\n[2] Enter hexadecimal\n[3] Enter binary\n[4] Enter octal\n[0] Exit\n");
    printf("Choose an option: ");
    scanf("%d", &op);
    CleanIn();

    switch (op) {
        case DECIMAL:
            printf("Enter a decimal number: ");
            scanf("%" SCNu64, &n);
            CleanIn();
            break;

        case HEX:
            printf("Enter a hex number (e.g., FF or 0xFF): ");
            scanf("%" SCNx64, &n);
            CleanIn();
            break;

        case BINARY:
            printf("Enter a binary number: ");
            scanf("%s", binary);
            CleanIn();
            n = bintoint64(binary);
            break;

        case OCT:
            printf("Enter an octal number: ");
            scanf("%" SCNo64, &n);
            CleanIn();
            break;

        case EXIT:
            goto leave;
            break;

        default:
            printf("Invalid option!\n");
            goto leave;
    }

    printf("\nDecimal: %" PRIu64 "\n", n);
    printf("Hexadecimal: 0x%" PRIX64 "\n", n);
    printf("Octal: 0%" PRIo64 "\n", n);

    printf("Binary: ");
    toBinary64(n);

leave:
    free(binary);
    return 0;
}

void CleanIn(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

uint64_t bintoint64(const char* bin) {
    uint64_t n = 0;
    for (int i = 0; bin[i]; i++) {
        n <<= 1;
        if (bin[i] == '1') n |= 1;
    }
    return n;
}

void toBinary64(uint64_t n) {
    int started = 0;
    for (int i = 63; i >= 0; i--) {
        int bit = (n >> i) & 1;
        if (bit) started = 1;
        if (started) printf("%d", bit);
    }
    if (!started) printf("0");
    printf("\n");
}