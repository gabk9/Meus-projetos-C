#include <stdio.h>

void myfunc(int initNum, int endNum);

int main() {
    int n;
    printf("Type-in a number: ");
    scanf("%d", &n);

    myfunc(0, n);

    return 0;
}

void myfunc(int initNum, int endNum) {
    printf("%d\n", initNum);
    if(initNum < endNum) {
        initNum++;
        myfunc(initNum, endNum);
    }
}