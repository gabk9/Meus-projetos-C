#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define TAM 41

void setCor(int cor);
void linha();
void CleanIn();
void buscarAluno();
void editarAluno();
void mostrarEstatisticas();
void cadastrar();
void dados();
void mostrarRanking();

typedef struct {
    int idade;
    float nota[2];
    float peso;
    char nome[100];
    float media;
} aluno;

HANDLE hConsole;
aluno turma[TAM];
int tam1 = 0;

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int op;

    do {
        system("cls");
        setCor(15); // Branco brilhante
        puts("\n===== MENU =====\n");
        setCor(9); // Azul claro
        puts("[1] Cadastrar alunos");
        puts("[2] Mostrar dados dos alunos");
        puts("[3] Mostrar ranking de alunos com maior média");
        puts("[4] Reescrever Alunos Cadastrados");
        puts("[5] Buscar aluno pelo nome");
        puts("[6] Editar dados de um aluno");
        puts("[7] Mostrar estatísticas da turma");
        puts("[8] Sair\n");

        setCor(7); // Branco padrão
        linha();
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        CleanIn();

        switch (op) {
            case 1: cadastrar(); break;
            case 2: dados(); break;
            case 3: mostrarRanking(); break;
            case 4:
                if (tam1 > 0) { tam1 = 0; cadastrar(); }
                else {
                    setCor(12); printf("\aNão há nada para reescrever!\n");
                    setCor(7); system("pause");
                } break;
            case 5: buscarAluno(); break;
            case 6: editarAluno(); break;
            case 7: mostrarEstatisticas(); break;
            case 8:
                setCor(4); // Vermelho
                printf("\nSaindo... Até logo!\n");
                setCor(7); // Branco padrão
                system("pause"); break;
            default:
                setCor(12); // Vermelho claro 
                printf("\a\nOpção inválida! Tente novamente.\n");
                setCor(7); // Branco padrão 
                system("pause"); break;
        }

    } while (op != 8);

    return 0;
}

void linha() {
    puts("\n------------------------------\n");
}

void CleanIn() {
    while((getchar()) !='\n');
}

void calcularMedias() {
    for (int i = 0; i < tam1; i++) {
        turma[i].media = (turma[i].nota[0] + turma[i].nota[1]) / 2.0f;
    }
}

void buscarAluno() {
    if (tam1 == 0) {
        setCor(12); // Vermelho claro
        printf("\aNenhum aluno cadastrado!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    char busca[100];
    setCor(14); // Amarelo claro
    printf("Digite o nome do aluno para buscar: ");
    setCor(7); // Branco padrão
    fgets(busca, 100, stdin);
    busca[strcspn(busca, "\n")] = 0;

    int encontrado = -1;
    for (int i = 0; i < tam1; i++) {
        if (strcasecmp(turma[i].nome, busca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        setCor(12); // Vermelho claro
        printf("Aluno não encontrado!\n");
        setCor(7); // Branco padrão
    } else {
        setCor(10); // Verde claro
        printf("Aluno encontrado: %s\n", turma[encontrado].nome);
        setCor(7); // Branco padrão
        printf("Deseja ver os dados? (s/n): ");
        char op = getchar();
        CleanIn();
        if (op == 's' || op == 'S') {
            setCor(11); // Aqua claro
            printf("Idade: %d\n", turma[encontrado].idade);
            printf("Peso: %.2f KG\n", turma[encontrado].peso);
            printf("Nota 1: %.2f\n", turma[encontrado].nota[0]);
            printf("Nota 2: %.2f\n", turma[encontrado].nota[1]);
            printf("Média: %.2f\n", turma[encontrado].media);
            setCor(7); // Branco padrão
        }
    }

    system("pause");
}

void editarAluno() {
    if (tam1 == 0) {
        setCor(12); // Vermelho claro
        printf("\aNenhum aluno cadastrado!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    char nome[100];
    setCor(14); // Amarelo claro
    printf("Digite o nome do aluno para editar: ");
    setCor(7); // Branco padrão
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int i;
    for (i = 0; i < tam1; i++) {
        if (strcasecmp(turma[i].nome, nome) == 0) break;
    }

    if (i == tam1) {
        setCor(12); // Vermelho claro
        printf("Aluno não encontrado!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    setCor(11); // Aqua claro
    printf("Editando dados de %s\n", turma[i].nome);
    setCor(7); // Branco padrão

    setCor(14); // Amarelo claro
    printf("Nova idade: ");
    setCor(7); // branco padrão
    scanf("%d", &turma[i].idade); CleanIn();

    setCor(14); // Amarelo claro
    printf("Novo peso: ");
    setCor(7); // Branco padrão
    scanf("%f", &turma[i].peso); CleanIn();

    for (int j = 0; j < 2; j++) {
        do {
            setCor(14); // Amaerlo claro
            printf("Nova nota %d: ", j + 1);
            setCor(7); // Branco padrão 
            scanf("%f", &turma[i].nota[j]); CleanIn();
        } while (turma[i].nota[j] < 0 || turma[i].nota[j] > 10);
    }

    calcularMedias();

    setCor(10); // Verde claro
    printf("Aluno editado com sucesso!\n");
    setCor(7); // Branco padrão
    system("pause");
}

void setCor(int cor) {
    SetConsoleTextAttribute(hConsole, cor);
}

void cadastrar() {
    int novos;

    if (tam1 == TAM) {
        setCor(12); // Vermelho claro
        printf("\aLimite máximo de alunos já cadastrados!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    setCor(11); // Aqua claro
    printf("Quantos alunos deseja cadastrar? (máx. %d): ", TAM - tam1);
    setCor(7); // Branco padrão
    scanf("%d", &novos);
    CleanIn();

    if (novos < 1 || tam1 + novos > TAM) {
        setCor(12); // Vermelho claro
        printf("\aQuantidade inválida!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    int novo_total = tam1 + novos;

    for (int i = tam1; i < novo_total; i++) {
        setCor(14); // Amarelo claro
        printf("Nome do aluno (%d): ", i + 1);
        setCor(7); // Branco padrão
        fgets(turma[i].nome, 100, stdin);
        turma[i].nome[strcspn(turma[i].nome, "\n")] = 0;

        setCor(14); // Amarelo claro
        printf("Idade do aluno (%d), que seja pelo menos 6 anos: ", i + 1);
        setCor(7); // Branco padrão
        scanf("%d", &turma[i].idade);
        CleanIn();
        if(turma[i].idade < 6) {
            setCor(12); // Vermelho claro
            printf("\aIdade inválida\n"); setCor(7);
            tam1 = 0;
            system("pause");
            return;
        }

        setCor(14); // Amarelo claro
        printf("Peso do aluno em KG (%d): ", i + 1);
        setCor(7); // branco padrão
        scanf("%f", &turma[i].peso);
        CleanIn();

        setCor(14); // Amarelo claro
        printf("Digite as duas notas do aluno (%d):\n", i + 1);
        setCor(7); // Branco padrão
        for (int j = 0; j < 2; j++) {
            do {
                printf("Nota %d: ", j + 1);
                scanf("%f", &turma[i].nota[j]);

                if (turma[i].nota[j] < 0 || turma[i].nota[j] > 10) {
                    setCor(4); // Vermelho
                    printf("\aNota inválida. Digite uma nota entre 0 e 10.\n");
                    setCor(7); // Branco padrão
                }
            } while (turma[i].nota[j] < 0 || turma[i].nota[j] > 10);
        }
        CleanIn(); 
        linha();
    }

    tam1 = novo_total;
    calcularMedias();

    setCor(10); // Verde claro
    printf("%d aluno(s) cadastrado(s) com sucesso!\n", novos);
    setCor(7); // Branco padrão
    system("pause");
}

void mostrarEstatisticas() {
    if (tam1 == 0) {
        setCor(12); // Vermelho
        printf("\aNenhum aluno cadastrado!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    float soma = 0, maior = turma[0].media, menor = turma[0].media;
    int i_maior = 0, i_menor = 0;

    for (int i = 0; i < tam1; i++) {
        soma += turma[i].media;
        if (turma[i].media > maior) {
            maior = turma[i].media;
            i_maior = i;
        }
        if (turma[i].media < menor) {
            menor = turma[i].media;
            i_menor = i;
        }
    }

    float media_geral = soma / tam1;

    setCor(11); // Aqua claro
    printf("Média geral da turma: %.2f\n", media_geral);
    setCor(10); // Verde claro
    printf("Maior média: %.2f (%s)\n", maior, turma[i_maior].nome);
    setCor(12); // Vermelho claro
    printf("Menor média: %.2f (%s)\n", menor, turma[i_menor].nome);
    setCor(7); // Branco padrão
    linha();
    system("pause");
}

void dados() {
    if (tam1 == 0) {
        setCor(12); // Vermelho claro
        printf("\aNenhum aluno cadastrado ainda!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    setCor(10); // Verde claro
    printf("======== DADOS ========\n");
    setCor(7); // Branco padrão
    for (int i = 0; i < tam1; i++) {
        printf("A média de ");
        setCor(14); // Amarelo claro
        printf("%s", turma[i].nome);
        setCor(7); // Branco padrão
        printf(" é: ");
        setCor(11); // Aqua claro
        printf("%.2f\n", turma[i].media); 
        setCor(7); // Branco padrão
        printf("O peso é ");
        setCor(4); // Vermelho
        printf("%.2f ", turma[i].peso);
        setCor(7); // Branco padrão
        printf("KG\n");
        printf("A idade é: ");
        setCor(6); // Amarelo
        printf("%d", turma[i].idade); 
        setCor(7); // Branco padrão 
        printf(" anos\n");
        linha();
    }
    system("pause");
}

void mostrarRanking() {
    if (tam1 == 0) {
        setCor(12); // Vermelho claro
        printf("\aNenhum aluno cadastrado ainda!\n");
        setCor(7); // Branco padrão
        system("pause");
        return;
    }

    aluno copia[TAM];
    for (int i = 0; i < tam1; i++) {
        copia[i] = turma[i];
    }

    for (int i = 0; i < tam1 - 1; i++) {
        for (int j = i + 1; j < tam1; j++) {
            if (copia[i].media < copia[j].media) {
                aluno temp = copia[i];
                copia[i] = copia[j];
                copia[j] = temp;
            }
        }
    }

    setCor(13); // Roxo claro
    printf("===== RANKING DOS ALUNOS (do MELHOR para o PIOR) =====\n");
    setCor(7);
    for (int i = 0; i < tam1; i++) {
        setCor(10); // Verde claro
        printf("%dº - ", i + 1);
        setCor(14); // Amarelo claro
        printf("%s ", copia[i].nome);
        setCor(7); // Branco padrão
        printf("| Média: ");
        setCor(11); // Aqua claro
        printf("%.2f\n", copia[i].media);
        setCor(7); // Branco padrão
    }
    linha();
    system("pause");
}
