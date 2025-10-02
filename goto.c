#include <stdio.h>

void myfunc();

int main(int argc, char **argv) {
    int n;

    printf("Type-in a number: ");
    scanf("%d", &n);

    if (n == 0) {
        goto print_0;
    }
    goto call_myfunc;

    goto errormsg;

print_0:
    printf("\nYou typed 0\n");

call_myfunc:
    myfunc();

errormsg:
    perror("\nError message!!\n");

leave:
    return 0;
}

void myfunc() {
    printf("\nThe function!\n");
}