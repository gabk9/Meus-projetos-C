#include <stdio.h>

void hello(void);
void (*retFunc(void))();

int main() {
    // array de ponteiros para funções como retFunc
    void (* (*f[])() )() = { retFunc };

    f[0]()();  // chama retFunc -> retorna hello -> chama hello
    return 0;
}

void hello(void) {
    printf("Hello!\n");
}

void (*retFunc(void))() {  // função que retorna ponteiro para função void(void)
    return hello;
}
