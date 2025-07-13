#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>

void setCor(int cor);
void typewriter(const char *texto, int delay_ms);
void linha();
float calcularIMCENIM();
float calcularIMCENM();
float calcularIMCPTIM();
float calcularIMCPTM();
void mostrarIMCEN();
void mostrarIMCPT();
int menuEn(int op);
int EnMenu();
int PtImMenu();
int PtMeMenu();
int menuPt(int op);
int menuPr(int op);
float comparacaoEn();
float comparacaoPt();

typedef struct {
    float peso;
    float altura;
    int idade;
    char nome[100];
    float IMC;
} tipoDados;

HANDLE hConsole;
tipoDados lista;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    menuPr(1);
    return 0;
}

void typewriter(const char *texto, int delay_ms) {
    while (*texto) {
        putchar(*texto);
        fflush(stdout);
        Sleep(delay_ms);
        texto++;
    }
}

void setCor(int cor) {
    SetConsoleTextAttribute(hConsole, cor);
}

void linha() {
    setCor(5); // Roxo
    puts("\n------------------------------\n");
    setCor(7); // Branco padrão
}

float comparacaoEn() {
    if (lista.IMC < 18.5) {
        setCor(4); // Vermelho
        puts("\nUnderweight\n");
    } else if (lista.IMC < 25) {
        setCor(6); // Amarelo
        puts("\nNormal weight\n");
    } else if (lista.IMC < 30) {
        setCor(12);
        puts("\nOverweight\n");
    } else {
        setCor(4); // Vermelho
        puts("\nObesity\n");
    }
    setCor(7);
    return lista.IMC;
}

float comparacaoPt() {
    if (lista.IMC < 18.5) {
        setCor(4); // Vermelho
        puts("\nAbaixo do peso\n");
    } else if (lista.IMC < 25) {
        setCor(6); // Amarelo
        puts("\nPeso normal\n");
    } else if (lista.IMC < 30) {
        setCor(12); // Vermelho claro
        puts("\nSobrepeso\n");
    } else {
        setCor(4); // Vermelho
        puts("\nObesidade\n");
    }
    setCor(7); // Branco padrão
    return lista.IMC;
}

float calcularIMCENIM() {
    printf("Tell me your ");
    setCor(2); // Verde
    printf("height ");
    setCor(7); // Branco padrão
    printf("in feet: ");
    scanf("%f", &lista.altura);
    limparBuffer();

    printf("\nNow tell me your ");
    setCor(4); // Vermelho
    printf("weight ");
    setCor(7); // Branco padrão
    printf("in Lb's: ");
    scanf("%f", &lista.peso);
    limparBuffer();

    system("cls");
    float alturaPolegadas = lista.altura * 12;
    lista.IMC = (lista.peso * 703) / (alturaPolegadas * alturaPolegadas);
    return lista.IMC;
}

float calcularIMCENM() {
    printf("Tell me your ");
    setCor(2); // Verde
    printf("height ");
    setCor(7); // Branco padrão
    printf("in cm: ");
    scanf("%f", &lista.altura);
    limparBuffer();

    printf("\nNow tell me your ");
    setCor(4); // Vermelho
    printf("weight ");
    setCor(7); // branco padrão
    printf("in KG: ");
    scanf("%f", &lista.peso);
    limparBuffer();

    system("cls");
    float alturaMetros = lista.altura / 100.0;
    lista.IMC = lista.peso / (alturaMetros * alturaMetros);
    return lista.IMC;
}

float calcularIMCPTIM() {
    printf("Me diga sua ");
    setCor(2); // Verde
    printf("altura ");
    setCor(7); // Branco padrão
    printf("em pés: ");
    scanf("%f", &lista.altura);
    limparBuffer();

    printf("\nMe diga seu ");
    setCor(4); // Vermelho
    printf("peso ");
    setCor(7); // Branco padrão
    printf("em LB's: ");
    scanf("%f", &lista.peso);
    limparBuffer();

    system("cls");
    float alturaPolegadas = lista.altura * 12;
    lista.IMC = (lista.peso * 703) / (alturaPolegadas * alturaPolegadas);
    return lista.IMC;
}

float calcularIMCPTM() {
    printf("Me diga sua ");
    setCor(2); // Verde
    printf("altura ");
    setCor(7); // Branco padrão
    printf("em cm: ");
    scanf("%f", &lista.altura);
    limparBuffer();

    printf("\nMe diga seu ");
    setCor(4); // Vermelho
    printf("peso ");
    setCor(7); // Branco padrão
    printf("em KG: ");
    scanf("%f", &lista.peso);
    limparBuffer();

    system("cls");
    float alturaMetros = lista.altura / 100.0;
    lista.IMC = lista.peso / (alturaMetros * alturaMetros);
    return lista.IMC;
}

void mostrarIMCEN() {
    system("cls");
    printf("Your BMI is: ");
    setCor(11);
    printf("%.2f\n", lista.IMC);
    setCor(7);
    comparacaoEn();
    system("pause");
}

void mostrarIMCPT() {
    system("cls");
    printf("Seu IMC é: ");
    setCor(11); // Aqua claro
    printf("%.2f\n", lista.IMC);
    setCor(7); // Branco padrão
    comparacaoPt();
    system("pause");
}

int EnMenu() {
    int op;
    do {
        system("cls");
        setCor(2); // Verde
        puts("\n===== BMI MENU =====\n");
        setCor(9);
        puts("[1] Show BMI");
        puts("[2] Recalculate");
        puts("[3] Return to previous menu");
        puts("[4] Exit\n");
        setCor(7);
        linha();
        printf("Choose an option: ");
        scanf("%d", &op);
        limparBuffer();

        switch (op) {
        case 1:
            mostrarIMCEN();
            break;
        case 2:
            if (calcularIMCENIM()) EnMenu();
            return 0;
        case 3:
            return 0; // volta ao menu anterior (menuEn)
        case 4:
            setCor(12); // Vermelho claro
            printf("\nLeaving... Cya!\n");
            setCor(7); // Branco padrão
            exit(0);
        default:
            setCor(12);
            puts("\n\aInvalid option!\n");
            setCor(7);
            system("pause");
            break;
        }
    } while (op != 4);
    return 0;
}

int PtImMenu() {
    int op;
    do {
        system("cls");
        setCor(2); // Verde
        puts("\n===== MENU IMC =====\n");
        setCor(9); // Azul claro
        puts("[1] Mostrar IMC");
        puts("[2] Recalcular");
        puts("[3] Retornar ao menu anterior");
        puts("[4] Sair\n");
        setCor(7); // Branco padrão
        linha();
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        switch (op) {
        case 1:
            mostrarIMCPT();
            break;
        case 2:
            if (calcularIMCPTIM()) PtImMenu();
            return 0;
        case 3:
            return 0; // volta ao menuPt
        case 4:
            setCor(12); // Vermelho claro
            printf("\nSaindo, até logo!\n");
            setCor(7); // Branco padrão
            exit(0);
        default:
            setCor(12); // Vermelho claro
            puts("\n\aOpção inválida!\n");
            setCor(7); // Branco padrão
            system("pause");
            break;
        }
    } while (op != 4);
    return 0;
}

int PtMeMenu() {
    int op;
    do {
        system("cls");
        setCor(2); // Verde
        puts("\n===== MENU IMC MÉTRICO =====\n");
        setCor(9); // Azul claro
        puts("[1] Mostrar IMC");
        puts("[2] Recalcular");
        puts("[3] Retornar ao menu anterior");
        puts("[4] Sair\n");
        setCor(7); // Branco padrão
        linha();
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        switch (op) {
        case 1:
            mostrarIMCPT();
            break;
        case 2:
            if (calcularIMCPTM()) PtMeMenu();
            return 0;
        case 3:
            return 0; // volta ao menuPt
        case 4:
            setCor(12); // Vermelho claro
            printf("\nSaindo, até logo!\n");
            setCor(7); // Branco padrão
            exit(0);
        default:
            setCor(12); // Vermelho claro
            puts("\n\aOpção inválida!\n");
            setCor(7); // Branco padrão
            system("pause");
            break;
        }
    } while (op != 4);
    return 0;
}

int menuEn(int op) {
    do {
        system("cls");
        setCor(2); // Verde
        puts("\n===== SYSTEM =====\n");
        setCor(9); // Azul claro
        puts("[1] Imperial");
        puts("[2] Metric");
        puts("[3] Return to language menu");
        puts("[4] Exit\n");
        setCor(7); // Branco padrão
        linha();
        printf("Choose an option: ");
        scanf("%d", &op);
        limparBuffer();

        switch (op) {
        case 1:
            calcularIMCENIM();
            EnMenu();
            break;
        case 2:
            calcularIMCENM();
            EnMenu();
            break;
        case 3:
            return 0; // volta ao menuPr
        case 4:
            setCor(4); // Vermelho
            printf("\nLeaving... Cya!\n");
            setCor(7);
            exit(0);
        default:
            setCor(12); // Vermelho claro
            printf("\a\nInvalid option! Try again.\n");
            setCor(7); // Branco padrão
            system("pause");
            break;
        }
    } while (op != 4);
    return 0;
}

int menuPt(int op) {
    do {
        system("cls");
        setCor(2);
        puts("\n===== SISTEMA =====\n");
        setCor(9);
        puts("[1] Imperial");
        puts("[2] Métrico");
        puts("[3] Retornar ao menu de idiomas");
        puts("[4] Sair\n");
        setCor(7);
        linha();
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        switch (op) {
        case 1:
            calcularIMCPTIM();
            PtImMenu();
            break;
        case 2:
            calcularIMCPTM();
            PtMeMenu();
            break;
        case 3:
            return 0; // volta ao menuPr
        case 4:
            setCor(4); // Vermelho
            printf("\nSaindo... Até logo!\n");
            setCor(7);
            exit(0);
        default:
            setCor(12); // Vermelho claro
            printf("\a\nOpção inválida! Tente denovo\n");
            setCor(7);
            system("pause");
            break;
        }
    } while (op != 4);
    return 0;
}

int menuPr(int op) {
    do {
        system("cls");
        setCor(2); // Verde
        puts("\n===== MENU =====\n");
        setCor(9); // Azul claro
        puts("[1] English");
        puts("[2] Português");
        puts("[3] Sair\n");
        setCor(7); // Branco padrão
        printf("Answer/Resposta: ");
        scanf("%d", &op);
        limparBuffer();

        switch (op) {
        case 1:
            system("cls");
            setCor(2); // Verde
            typewriter("Welcome to the BMI calculator!!\n", 40);
            setCor(7); // Branco padrão
            Sleep(1500);
            if (menuEn(1) == -1) return 0;
            system("cls");
            break;
        case 2:
            system("cls");
            setCor(2); // Verde
            typewriter("Seja bem vindo à calculadora de IMC!!\n", 40);
            setCor(7); // Branco padrão
            Sleep(1500);
            if (menuPt(1) == -1) return 0;
            system("cls");
            break;
        case 3:
            setCor(4);  // Vermelho
            printf("\nLeaving/Saindo!\n");
            setCor(7); // Branco padrão
            return 0;
        default:
            setCor(12); // Vermelho claro
            printf("\a\nERROR!!\n");
            setCor(7); // Branco padrão
            system("pause");
            break;
        }
    } while (op != 3);
    return 0;
}
