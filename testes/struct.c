#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} Person;

void updateStruct(Person *p, char *NAME, int AGE);

int main() {
    Person *lowlevelearning = (Person *)malloc(sizeof(Person));
    char nm[50];
    int n;

    if(!lowlevelearning) {
        printf("\nError during struct allocation!!\n");
        return 1;
    }

    printf("Tell me your name: ");
    fgets(nm, sizeof(nm), stdin);
    nm[strcspn(nm, "\n")] = '\0';

    printf("Tell me your age: ");
    scanf("%d", &n);

    updateStruct(lowlevelearning, nm, n);

    printf("\n\nThe name saved on the struct is: %s\n", lowlevelearning->name);
    printf("The age saved on the struct is: %d\n", lowlevelearning->age);

    free(lowlevelearning);
    return 0;
}

void updateStruct(Person *p, char *NAME, int AGE) {
    strcpy(p->name, NAME);
    p->age = AGE;
}
