#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #define Clear() system("cls")
    #define Pause() system("pause")
    #define SleepMS(ms) Sleep(ms)
#elif defined(__linux__) || defined(__APPLE__) 
    #include <unistd.h>
    #define Clear() system("clear")
    #define Pause() do { \
        printf("\nPress ENTER to continue..."); \
        getchar(); \
    } while(0)
    #define SleepMS(ms) usleep((ms) * 1000)
#else 
    #error "Operational system not recognized, terminating program!!\n"
#endif


#define MAX_CHAR 50
#define MAX_ITEMS 100
#define MAX_FILE_ITEMS 100
#define MAX_PATH_LEN 260

typedef struct {
    float price[MAX_ITEMS];
    int qty[MAX_ITEMS];
    char name[MAX_ITEMS][MAX_CHAR];
    char unit[MAX_ITEMS][MAX_CHAR];
    float pricePQ[MAX_ITEMS];
} Item;


void Vload(int ms);
void Credits(char *buff);
void CleanStr(char *var);
void tolowerStr(char *str);
void type(char *text, int ms);
void delete(char *text, int ms);
void eraseData(Item *items, char *buff);
FILE *accessFile(char *fileDir, char *act);
char *strcasestr(const char *src, const char *sub); //! also not made by me
void edit(Item *items, int *totalItems, char *buff);
void save(Item *items, int *totalItems, char *buff);
void list(Item *items, int *totalItems, char *buff);
void erase(Item *items, int *totalItems, char *buff);
void search(Item *items, int *totalItems, char *buff);
void regist(Item *items, int *totalItems, char *buff);
void compare(Item *items, int *totalItems, char *buff);
void getFilePath(char *fullPath, size_t size, const char *fileName); //! it wasn't me who did this


int main(int argc, char **argv) {
#ifdef _WIN32
    printf("Running on Windows!!\n");
#elif __linux__
    printf("Running on Linux!!\n");
#elif __APPLE__
    printf("Running on Mac!!\n");
#else
    printf("Operational system not recognized, terminating program!!\n");
    goto leave;
#endif

    int op, typeSpeed = 2;
    char *buff = (char *)calloc(MAX_CHAR, sizeof(char));
    
    memset(buff, 0, MAX_CHAR);

    if(!buff) {
        printf("\nError: Allocation error!\n");
        return 1;
    }


    Vload(20);
    Clear();

    Item items = {0};
    int totalItems = 0;

    do {
        printf("========BuySmart========\n");
        type("[1] Register an item\n[2] Compare items\n[3] Save items\n", typeSpeed);
        type("[4] List items\n[5] Search items\n[6] Edit item\n[7] Remove item\n", typeSpeed);
        type("[8] Credits\n[9] Erase data\n[0] Exit program\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch(op) {
            case 1:
                regist(&items, &totalItems, buff);
                Pause();
                break;
            case 2:
                compare(&items, &totalItems, buff);
                Pause();
                break;
            case 3:
                save(&items, &totalItems, buff);
                Pause();
                break;
            case 4:
                list(&items, &totalItems, buff);
                Pause();
                break;
            case 5:
                search(&items, &totalItems, buff);
                Pause();
                break;
            case 6:
                edit(&items, &totalItems, buff); //! Currently working on it
                Pause();
                break;
            case 7:
                erase(&items, &totalItems, buff);
                Pause();
                break;
            case 8:
                Credits(buff);
                Pause();
                break;
            case 9:
                eraseData(&items, buff);
                Pause();
                break;
            case 0:
                printf("\nTerminating program, Bye!!\n");
                Pause();
                goto leave; //* I'm using goto because why not LOL
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
        }

        Clear();

    } while(op != 0);

    
leave:
    free(buff);
    return 0;
}

void Vload(int ms) {
    int total = 30;
    for(int i = 0; i <= total; i++) {
        int percent = (i * 100) / total;
        printf("\r[");

        for(int j = 0; j < i; j++)
            printf("#");

        for(int k = i; k < total; k++)
            printf(" ");

        printf("] %3d%%", percent);
        fflush(stdout);
        SleepMS(ms);
    }
    printf("\n");
}

void eraseData(Item *items, char *buff) {
    Clear();
    int op;
    static int typeSpeed = 7;
    do {
        printf("========Erase Data Menu========\n");
        type("[1] Erase all data\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch(op) {
            case 1: {
                FILE *file = accessFile("BuySmart.txt", "w");
                memset(items, 0, sizeof(items));

                printf("\nData deleted Successfully!!\n");
                Pause();
                Clear();
                break;
            }
            case 0:
                return;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
        }
    } while(op != 0);
}

void edit(Item *items, int *totalItems, char *buff) {
    Clear();
    int op; 
    static int typeSpeed = 7;
    
    do {
        printf("========Edit Menu========\n");
        type("[1] Read from file\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL;
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch (op) {
            case 1: {
                char line[1024];
                char **tempName = calloc(MAX_ITEMS, sizeof(char *));
                char *itemName = calloc(MAX_CHAR, sizeof(char));
                FILE *file = accessFile("BuySmart.txt", "r");

                fseek(file, 0, SEEK_END);
                long fileSize = ftell(file);
                rewind(file);

                if(!tempName || !itemName) {
                    printf("\nError: Allocation error!\n");
                    free(itemName);
                    free(tempName);
                    break;
                }

                for(size_t i = 0; i < MAX_ITEMS; i++) {
                    tempName[i] = calloc(MAX_CHAR, sizeof(char));

                    if (!tempName[i]) {
                        printf("\nError: Array allocation error!\n");
                        for (size_t j = 0; j < i; j++) free(tempName[j]);
                        free(tempName);
                        free(itemName);
                        break;
                    }
                }

                if(!file) {
                    printf("\nError: %s\n", strerror(errno));
                    Pause();
                    Clear();

                    for(size_t i = 0; i < MAX_ITEMS; i++) free(tempName[i]);
                    free(tempName);
                    free(itemName);
                    break;
                }

                if(!fileSize) {
                    printf("\nError: No items found in file\n");
                    Pause();
                    Clear();
                    break;
                }

                int itemCount = 0;
                while(fgets(line, sizeof(line), file) != NULL && itemCount < MAX_ITEMS) {
                    if(strncmp(line, "Name:", 5) == 0) {
                        sscanf(line, "Name: %49[^\n]", tempName[itemCount]);
                        itemCount++;
                    }
                }

                Clear();
                printf("========Editing========\n");
                printf("Names from file:\n");
                for(int i = 0; i < itemCount; i++) {
                    printf("[%d] %s\n", i + 1, tempName[i]);
                }

                printf("Type-in the name of the item to edit: ");
                fgets(itemName, MAX_CHAR, stdin);
                CleanStr(itemName);

                rewind(file);
                int found = 0;

                do {
                    Clear();
                    printf("========Editing========\n");
                    while(fgets(line, sizeof(line), file) != NULL) {
    
                        if(strncmp(line, "Name:", 5) == 0 && strcasestr(line, itemName)) {
                            printf("%s", line);
                            for(int i = 0; i < 3; i++) {
                                if(fgets(line, sizeof(line), file))
                                    printf("%s", line);
                            }
                            found = 1;
                            break;
                        }
                    }
                    
                    if(!found) {
                    printf("Item not found.\n");
                        break;
                    }

                    typeSpeed = 9;
                    type("\n[1] Start editing\n[0] Cancel\n", typeSpeed);
                    typeSpeed = 0;
    
                    buff = realloc(buff, MAX_CHAR);
                    printf("Choose an option: ");
                    fgets(buff, MAX_CHAR, stdin);

                    if(sscanf(buff, "%d", &op) != 1) {
                        errno = EINVAL; //* Invalid Arguments ERROR;
                        perror("\nError");
                        Pause();
                        Clear();
                        continue;
                    }

                    switch(op) {
                        case 1: {
                            rewind(file);
                            while(fgets(line, sizeof(line), file) != NULL) {
                                if(strncmp(line, "Name:", 5) == 0 && strcasestr(line, itemName)) {
                                    // TODO: continue here
                                }
                            }

                            rewind(file);
                            break;
                        }
                        case 0:
                            return;
                        default:
                            errno = EPERM;
                            perror("\nError");
                            Pause();
                            Clear();
                    }
                    break;
                    
                } while (op != 0);


                for(size_t i = 0; i < MAX_ITEMS; i++) 
                    free(tempName[i]);

                free(tempName);
                free(itemName);
                fclose(file);

                Pause();
                Clear();
                break;
            }
            case 0:
                return;
            default:
                errno = EPERM;
                perror("\nError");
                Pause();
                Clear();
        }

    } while (op != 0);
}

void erase(Item *items, int *totalItems, char *buff) {
    Clear();
    int op; 
    static int typeSpeed = 7;

    do {
        printf("========Remove Menu========\n");
        type("[1] Read from file\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL;
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch (op) {
            case 1: {
                char line[1024];
                char **tempName = calloc(MAX_ITEMS, sizeof(char *));
                char *itemName = calloc(MAX_CHAR, sizeof(char));
                FILE *file = accessFile("BuySmart.txt", "r");
                FILE *temp = accessFile("temp.txt", "w");

                fseek(file, 0, SEEK_END);
                long fileSize = ftell(file);
                rewind(file);
                
                if(!tempName || !itemName) {
                    printf("\nError: Allocation error!\n");
                    free(itemName);
                    free(tempName);
                    break;
                }

                for(size_t i = 0; i < MAX_ITEMS; i++) {
                    tempName[i] = calloc(MAX_CHAR, sizeof(char));

                    if (!tempName[i]) {
                        printf("\nError: Array allocation error!\n");
                        for (size_t j = 0; j < i; j++) 
                            free(tempName[j]);

                        free(tempName);
                        free(itemName);
                        break;
                    }
                }
                

                if(!file) {
                    printf("\nError: %s\n", strerror(errno));
                    Pause();
                    Clear();

                    for(size_t i = 0; i < MAX_ITEMS; i++) free(tempName[i]);
                    free(tempName);
                    free(itemName);
                    break;
                }

                if(!fileSize) {
                    printf("\nError: No items found in file\n");
                    Pause();
                    Clear();
                    break;
                }

                rewind(file);

                int itemCount = 0;
                while(fgets(line, sizeof(line), file) != NULL && itemCount < MAX_ITEMS) {
                    if(strncmp(line, "Name:", 5) == 0) {
                        sscanf(line, "Name: %49[^\n]", tempName[itemCount]);
                        itemCount++;
                    }
                }

                Clear();
                printf("========Removing========\n");
                printf("Names from file:\n");
                for(int i = 0; i < itemCount; i++) {
                    printf("[%d] %s\n", i + 1, tempName[i]);
                }

                printf("Type-in the name of the item to remove: ");
                fgets(itemName, MAX_CHAR, stdin);
                CleanStr(itemName);

                rewind(file);
                int found = 0;
                int removed  = 0;
                int fclosed = 0;

                do {
                    Clear();
                    printf("========Removing========\n");
                    while(fgets(line, sizeof(line), file) != NULL) {
    
                        if(strncmp(line, "Name:", 5) == 0 && strcasestr(line, itemName)) {
                            printf("%s", line);
                            for(int i = 0; i < 3; i++) {
                                if(fgets(line, sizeof(line), file))
                                    printf("%s", line);
                            }
                            found = 1;
                            break;
                        }
                    }
                    
                    if(!found) {
                    printf("Item not found.\n");
                        break;
                    }

                    typeSpeed = 9;
                    type("\n[1] Remove\n[0] Cancel\n", typeSpeed);
                    typeSpeed = 0;
    
                    buff = realloc(buff, MAX_CHAR);
                    printf("Choose an option: ");
                    fgets(buff, MAX_CHAR, stdin);

                    if(sscanf(buff, "%d", &op) != 1) {
                        errno = EINVAL; //* Invalid Arguments ERROR;
                        perror("\nError");
                        Pause();
                        Clear();
                        continue;
                    }

                   

                    switch(op) {
                        case 1: 
                            rewind(file);
                            while(fgets(line, sizeof(line), file) != NULL) {
                                if(strncmp(line, "Name:", 5) == 0 && strcasestr(line, itemName)) {

                                    for(int i = 0; i < 4; i++) {
                                        fgets(line, sizeof(line), file);
                                    }
                                } else {
                                    fputs(line, temp);
                                }
                            }
                            fclose(file);
                            fclose(temp);
                            fclosed = 1;

                            printf("\nSuccessfully removed!!\n");

                            rewind(file);
                            removed = 1;
                            break;
                        case 0:
                            return;
                        default:
                            errno = EPERM;
                            perror("\nError");
                            Pause();
                            Clear();
                }
                    break;
                    
                } while (op != 0);


                for(size_t i = 0; i < MAX_ITEMS; i++) 
                    free(tempName[i]);

                free(tempName);
                free(itemName);

                if(!fclosed) {
                    fclose(file);
                    fclose(temp);
                }

                if(removed) {
                    remove("BuySmart.txt");
                    rename("temp.txt", "BuySmart.txt");
                }

                rewind(file);

                Pause();
                Clear();
                break;
            }
            case 0:
                return;
            default:
                errno = EPERM;
                perror("\nError");
                Pause();
                Clear();
        }

    } while (op != 0);
}

void search(Item *items, int *totalItems, char *buff) {
    Clear();
    int op; 
    static int typeSpeed = 7;

    do {
        printf("========Search Menu========\n");
        type("[1] Read from file\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL;
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch (op) {
            case 1: {
                char line[1024];
                char **tempName = calloc(MAX_ITEMS, sizeof(char *));
                char *itemName = calloc(MAX_CHAR, sizeof(char));
                FILE *file = accessFile("BuySmart.txt", "r");
                
                fseek(file, 0, SEEK_END);
                long fileSize = ftell(file);
                rewind(file);
                
                if(!tempName || !itemName) {
                    printf("\nError: Allocation error!\n");
                    free(itemName);
                    free(tempName);
                    break;
                }

                for(size_t i = 0; i < MAX_ITEMS; i++) {
                    tempName[i] = calloc(MAX_CHAR, sizeof(char));

                    if (!tempName[i]) {
                        printf("\nError: Array allocation error!\n");
                        for (size_t j = 0; j < i; j++)
                            free(tempName[j]);
                            
                        free(tempName);
                        free(itemName);
                        break;
                    }
                }

                if(!file) {
                    printf("\nError: %s\n", strerror(errno));
                    Pause();
                    Clear();

                    for(size_t i = 0; i < MAX_ITEMS; i++) 
                        free(tempName[i]);

                    free(tempName);
                    free(itemName);
                    break;
                }

                if(!fileSize) {
                    printf("\nError: No items found in file\n");
                    Pause();
                    Clear();
                    break; 
                }

                int itemCount = 0;
                while(fgets(line, sizeof(line), file) != NULL && itemCount < MAX_ITEMS) {
                    if(strncmp(line, "Name:", 5) == 0) {
                        sscanf(line, "Name: %49[^\n]", tempName[itemCount]);
                        itemCount++;
                    }
                }

                Clear();
                printf("========Searching========\n");
                printf("Names from file:\n");
                for(int i = 0; i < itemCount; i++) {
                    printf("[%d] %s\n", i + 1, tempName[i]);
                }

                printf("Type-in the name of the item to search: ");
                fgets(itemName, MAX_CHAR, stdin);
                CleanStr(itemName);

                rewind(file);
                int found = 0;
                printf("\n");
                while(fgets(line, sizeof(line), file) != NULL) {

                    if(strncmp(line, "Name:", 5) == 0 && strcasestr(line, itemName)) {
                        printf("%s", line);
                        for(int i = 0; i < 3; i++) {
                            if(fgets(line, sizeof(line), file))
                                printf("%s", line);
                        }
                        found = 1;
                        break;
                    }
                }
                printf("\n");

                if(!found) {
                    printf("Item not found.\n");
                }

                for(size_t i = 0; i < MAX_ITEMS; i++) 
                    free(tempName[i]);

                free(tempName);
                free(itemName);
                fclose(file);

                Pause();
                Clear();
                break;
            }
            case 0:
                return;
            default:
                errno = EPERM;
                perror("\nError");
                Pause();
                Clear();
        }

    } while (op != 0);
}

void save(Item *items, int *totalItems, char *buff) {
    Clear();
    int op;
    static int typeSpeed = 7;

    do {
        printf("========Save Menu========\n");
        type("[1] Save items\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR
            perror("\nError");
            Pause();
            Clear();
            continue;            
        }

        switch(op) {
            case 1: {
                FILE *file = accessFile("BuySmart.txt", "a");
                if(!file) {
                    printf("\nError: Couldn't open the file!\n");
                    Pause();
                    Clear();
                    return;
                } else {
                    fseek(file, 0, SEEK_END);
                }

                for(int i = 0; i < *totalItems; i++) {
                    items->pricePQ[i] = items->price[i] / (float)items->qty[i];
                    fprintf(file, "Name: %s\n", items->name[i]);
                    fprintf(file, "Price: %.2fR$\n", items->price[i]);
                    fprintf(file, "Total amount in \"%s\": %d\n", items->unit[i], items->qty[i]);
                    fprintf(file, "Price Per Quantity: %.2fR$\n\n", items->pricePQ[i]);
                }
            
                fclose(file);

                memset(items, 0, sizeof(*items));
                *totalItems = 0;
                
                printf("\nSaved successfully!\n");
                Pause();
                Clear();

                break;
            }
            case 0:
                return;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();                
        }
    } while (op != 0);
}

void Credits(char *buff) {
    Clear();
    int loopCount = 0, op;
    static int typeSpeed = 7;
    char *strings[] = {"Made by: Gabriel Oliveira Miranda",
                       "a high school freshman",
                       "this code is still in beta!"};
    
    do {
        printf("========Credits Menu========\n");
        type("[1] Credits screen\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;
    
        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);
    
        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch(op) {
            case 1:
                Clear();
                while(loopCount != 2) {
                    for(int i = 0; i < 3; i++) {
                        type(strings[i], 35);
                        SleepMS(550);
                        delete(strings[i], 25);
                    }
                    loopCount++;
                }
                printf("You saw all the credits, now we're heading back\n");
                break;
            case 0:
                return;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
        }

    } while (op != 1);
}

void list(Item *items, int *totalItems, char *buff) {
    Clear();
    FILE *file = accessFile("BuySmart.txt", "r");
    int op;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    static int typeSpeed = 7;

    do {
        printf("========List Menu========\n");
        type("[1] List items\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR
            perror("\nError");
            Pause();
            Clear();
            continue;            
        }

        switch(op) {
            case 1: {
                int fileCount = 0;
                char line[1024];

                if(!fileSize) {
                    printf("\nError: No items found in file\n");
                    Pause();
                    Clear();
                    break;
                }

                printf("Items list:\n\n");

                if(!file) {
                    printf("\nError: %s\n", strerror(errno));
                    Pause();
                    Clear();
                    return;
                }

                rewind(file);

                while(fgets(line, sizeof(line), file) != NULL && fileCount < MAX_ITEMS) {
                    printf("%s", line);
                }
                Pause();
                Clear();
                break;        
            } 
            case 0: 
                return;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();                
        }

    } while(op != 0);

    fclose(file);
}

void compare(Item *items, int *totalItems, char *buff) {
    Clear();
    int op;
    static int typeSpeed = 7;

    Item fileItems = {0};
    int fileCount = 0;

    do {
        printf("========Compare Menu========\n");
        type("[1] Compare items\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) == 1) {
            switch(op) {
                case 1: {
                    FILE *file = accessFile("BuySmart.txt", "r");

                    if(!file) {
                        printf("\nError: %s\n", strerror(errno));
                        Pause();
                        Clear();
                        break;
                    }

                    fileCount = 0;
                    char line[1024];
                    char tempName[MAX_CHAR] = "";
                    float tempPrice = 0.0f;
                    int tempQty = 0;

                    while(fgets(line, sizeof(line), file) != NULL && fileCount < MAX_ITEMS) {
                        if(strncmp(line, "Name:", 5) == 0) {
                            sscanf(line, "Name: %49[^\n]", tempName);
                        }
                        else if(strncmp(line, "Price:", 6) == 0) {
                            sscanf(line, "Price: %fR$", &tempPrice);
                        }
                        else if(strncmp(line, "Total amount in", 15) == 0) {
                            char *colonPos = strrchr(line, ':');
                            if (colonPos) {
                                sscanf(colonPos + 1, "%d", &tempQty);
                            }

                            strncpy(fileItems.name[fileCount], tempName, MAX_CHAR - 1);
                            fileItems.name[fileCount][MAX_CHAR - 1] = '\0';
                            fileItems.price[fileCount] = tempPrice;
                            fileItems.qty[fileCount] = tempQty;

                            fileCount++;

                            tempName[0] = '\0';
                            tempPrice = 0.0f;
                            tempQty = 0;
                        }
                    }
                    fclose(file);

                    if(!fileCount) {
                        printf("\nError: No items found in file\n");
                        Pause();
                        Clear();
                        break;
                    }

                    printf("\nNames from file:\n");
                    for (int i = 0; i < fileCount; i++) {
                        printf("[%d] %s\n", i + 1, fileItems.name[i]);
                    }

                    printf("\nSelect items to compare by number (e.g. 1 3 5): ");
                    fgets(buff, MAX_CHAR, stdin);
                    CleanStr(buff);

                    int selected[MAX_ITEMS];
                    int selectedCount = 0;
                    char *token = strtok(buff, " ");
                    while(token != NULL && selectedCount < MAX_ITEMS) {
                        int idx = atoi(token);
                        if (idx >= 1 && idx <= fileCount) {
                            selected[selectedCount++] = idx - 1;
                        }
                        token = strtok(NULL, " ");
                    }

                    if(selectedCount == 0) {
                        printf("\nError: No valid items selected.\n");
                        Pause();
                        Clear();
                        break;
                    }

                    printf("\nSelected items from file with Price per Quantity:\n");

                    float bestPricePQ = 1e9f;
                    int bestIndex = -1;

                    for(int i = 0; i < selectedCount; i++) {
                        int idx = selected[i];
                        if(fileItems.qty[idx] == 0) {
                            printf("- %s: Quantity is zero, cannot calculate price per quantity\n", fileItems.name[idx]);
                            continue;
                        }
                        float pricePQ = fileItems.price[idx] / (float)fileItems.qty[idx];
                        printf("- %s: Price per Quantity = %.2f\n", fileItems.name[idx], pricePQ);

                        if(pricePQ < bestPricePQ) {
                            bestPricePQ = pricePQ;
                            bestIndex = idx;
                        }
                    }

                    if(bestIndex != -1) {
                        printf("\nBest item based on Price per Quantity:\n");
                        printf("-> %s with %.2f per unit\n", fileItems.name[bestIndex], bestPricePQ);
                    } else {
                        printf("\nNo valid items to compare.\n");
                    }

                    rewind(file);

                    Pause();
                    Clear();
                    break;
                }
                case 0:
                    return;
                default:
                    errno = EPERM; //* Operation not permited ERROR
                    perror("\nError");
                    Pause();
                    Clear();
            }
        } else {
            errno = EINVAL;
            perror("\nError");
            Pause();
            Clear();
            continue;
        }
    } while(op != 0);
}

void regist(Item *items, int *totalItems, char *buff) {
    Clear();
    int qty, op, validInput = 0;
    static int typeSpeed = 7;

    do {
        printf("========Register Menu========\n");
        type("[1] Register item\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);

        if(sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR;
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch(op) {
            case 1:
                do {
                    buff = realloc(buff, MAX_CHAR);
                    printf("How many items you wish to add? ");
                    fgets(buff, MAX_CHAR, stdin);
                    CleanStr(buff);
        
                    if(sscanf(buff, "%d", &qty) != 1 || qty <= 0) {
                        errno = EINVAL; //* Invalid Arguments ERROR;
                        perror("\nError");
                        Pause();
                        Clear();
                        break;
                    }

                    validInput = 1;

                    if(*totalItems + qty > MAX_ITEMS) {
                        printf("\nError: You can only add up to %d items total.\n", MAX_ITEMS);
                        Pause();
                        Clear();
                        continue;
                    }
                } while (qty <= 0);

                if(validInput) {
                    for(int i = 0; i < qty; i++) {
                        printf("\nName of the Item n%d: ", *totalItems + 1);
                        fgets(items->name[*totalItems], MAX_CHAR, stdin);
                        CleanStr(items->name[*totalItems]);
                        
                        printf("What is the unit of measurement? (KG, G, ML, L, Unit) ");
                        fgets(items->unit[*totalItems], MAX_CHAR, stdin);
                        CleanStr(items->unit[*totalItems]);
                        
                        printf("Price in R$: ");
                        fgets(buff, MAX_CHAR, stdin);
                        sscanf(buff, "%f", &items->price[*totalItems]);
                        
                        printf("Total amount in \"%s\": ", items->unit[*totalItems]);
                        fgets(buff, MAX_CHAR, stdin);
                        sscanf(buff, "%d", &items->qty[*totalItems]);
                        
                        (*totalItems)++;
                    }
                    printf("\nItem(s) registered in cache\n");
                    Pause();
                    Clear();
                }
                break;
            case 0:
                return;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
                
        }
    } while (op != 0);
}

void CleanStr(char *var) {
    var[strcspn(var, "\n")] = '\0';
}

void type(char *text, int ms) {
    for(int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        SleepMS(ms);
    }
}

void delete(char *text, int ms) {
    int len = strlen(text) - 1;
    for(int i = len; i >= 0; i--) {
        printf("\b \b");
        fflush(stdout);
        SleepMS(ms);
    } 
}

void tolowerStr(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

char *strcasestr(const char *src, const char *sub) { //! also not made by me
    static char lowerSrc[1024];
    static char lowerSub[256];

    strncpy(lowerSrc, src, sizeof(lowerSrc) - 1);
    lowerSrc[sizeof(lowerSrc) - 1] = '\0';
    strncpy(lowerSub, sub, sizeof(lowerSub) - 1);
    lowerSub[sizeof(lowerSub) - 1] = '\0';

    tolowerStr(lowerSrc);

    tolowerStr(lowerSub);

    char *pos = strstr(lowerSrc, lowerSub);
    return pos ? (char *)(src + (pos - lowerSrc)) : NULL;
}

FILE *accessFile(char *fileDir, char *act) {
    char filePath[MAX_PATH_LEN];
    getFilePath(filePath, sizeof(filePath), fileDir);
    FILE *file = fopen(filePath, act);
    return file;
}

void getFilePath(char *fullPath, size_t size, const char *fileName) { //! it wasn't me who did this
#ifdef _WIN32
    char pathEXE[MAX_PATH_LEN];
    GetModuleFileName(NULL, pathEXE, MAX_PATH_LEN);

    char* p = strrchr(pathEXE, '\\');
    if (p) {
       *(p + 1) = '\0';
    }

    snprintf(fullPath, size, "%s%s", pathEXE, fileName);
#else

    snprintf(fullPath, size, "./%s", fileName);
#endif
}