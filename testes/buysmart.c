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
} Item;


void Credits();
void Vload(int ms);
void CleanStr(char *var);
void tolowerStr(char *str); //! also not made by me
void type(char *text, int ms);
void delete(char *text, int ms);
FILE* accessFile(char *fileName, char *act);
char *strcasestr(const char *src, const char *sub); //! also not made by me
void search(Item *items, int totalItems, char *buff);
void saveItem(Item *items, int totalItems, char *buff);
void readItem(Item *items, int totalItems, char *buff);
void registItem(Item *items, int *totalItems, char *buff);
void compareItem(Item *items, int *totalItems, char *buff);
void getFilePath(char *fullPath, size_t size, const char *fileName); //! it wasn't me who did this


int main(int argc, char **argv) {
    int op, typeSpeed = 2;
    char *buff = (char *)calloc(MAX_CHAR, sizeof(char));
    
    memset(buff, 0, MAX_CHAR);

    if (!buff) {
        printf("\nError: Allocation error!\n");
        return 1;
    }

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

    Vload(20);
    Clear();

    Item items = {0};
    int totalItems = 0;

    do {
        printf("========BuySmart========\n");
        type("[1] Register an item\n[2] Compare items\n[3] Save items\n[4] List items\n[5] Search items\n[6] Edit item\n[7] Remove item\n[8] Credits\n[0] Exit program\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if (sscanf(buff, "%d", &op) != 1) {
            errno = EINVAL; //* Invalid Arguments ERROR
            perror("\nError");
            Pause();
            Clear();
            continue;
        }

        switch(op) {
            case 1:
                registItem(&items, &totalItems, buff);
                Pause();
                break;
            case 2:
                compareItem(&items, &totalItems, buff);
                Pause();
                break;
            case 3:
                saveItem(&items, totalItems, buff);
                Pause();
                break;
            case 4:
                readItem(&items, totalItems, buff);
                Pause();
                break;
            case 5:
                search(&items, totalItems, buff);
                Pause();
                break;
            case 6:
                // TODO: Implement edit item
                printf("\n\"Edit item\" not implemented yet.\n");
                Pause();
                break;
            case 7:
                // TODO: Implement remove item
                printf("\n\"Remove item \" not implemented yet.\n");
                Pause();
                break;
            case 8:
                Credits();
                Pause();
                break;
            case 0:
                printf("\nTerminating program, Bye!!\n");
                Pause();
                goto leave; //* I'm using goto because why not LOL
                break;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
        }

        Clear();

    } while(1);

    free(buff);

leave:
    return 0;
}

void Vload(int ms) {
    int total = 30;
    for (int i = 0; i <= total; i++) {
        int percent = (i * 100) / total;
        printf("\r[");

        for (int j = 0; j < i; j++) {
            printf("#");
        }

        for (int k = i; k < total; k++) {
            printf(" ");
        }

        printf("] %3d%%", percent);
        fflush(stdout);
        SleepMS(ms);
    }
    printf("\n");
}

void search(Item *items, int totalItems, char *buff) {
    Clear();
    int op, typeSpeed = 7;

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
                Clear();
                char line[1024];
                char **tempName = calloc(MAX_ITEMS, sizeof(char *));
                char *itemName = calloc(MAX_CHAR, sizeof(char));

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

                FILE *file = accessFile("BuySmart.txt", "r");
                if(!file) {
                    printf("\nError: %s\n", strerror(errno));
                    Pause();
                    Clear();

                    for(size_t i = 0; i < MAX_ITEMS; i++) free(tempName[i]);
                    free(tempName);
                    free(itemName);
                    break;
                }

                int itemCount = 0;
                while(fgets(line, sizeof(line), file) != NULL && itemCount < MAX_ITEMS) {
                    if(strncmp(line, "Name:", 5) == 0) {
                        sscanf(line, "Name: %49[^\n]", tempName[itemCount]);
                        itemCount++;
                    }
                }

                printf("Names from file:\n");
                for(int i = 0; i < itemCount; i++) {
                    printf("[%d] %s\n", i + 1, tempName[i]);
                }

                printf("Search item in list: ");
                fgets(itemName, MAX_CHAR, stdin);
                CleanStr(itemName);

                rewind(file);
                int found = 0;
                printf("\n");
                while(fgets(line, sizeof(line), file) != NULL) {

                    if(strncmp(line, "Name:", 5) == 0 && strcasestr(line, itemName)) {
                        printf("%s", line);
                        for(int i = 0; i < 3; i++) {
                            if(fgets(line, sizeof(line), file)) // TODO: Improve the line printing
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

                for(size_t i = 0; i < MAX_ITEMS; i++) free(tempName[i]);
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

void saveItem(Item *items, int totalItems, char *buff) {
    Clear();
    int op, typeSpeed = 7;
    do {
        printf("========Save Menu========\n");
        type("[1] Save\n[0] Return to main menu\n", typeSpeed);
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
                FILE *file = accessFile("BuySmart.txt", "r+");
                if (!file) {
                    file = accessFile("BuySmart.txt", "w");
                    if (!file) {
                        printf("\nError: Couldn't open the file!\n");
                        Pause();
                        Clear();
                        return;
                    }
                } else {
                    fseek(file, 0, SEEK_END);
                }

                for(int i = 0; i < totalItems; i++) {
                    float pricePQ = items->price[i] / (float)items->qty[i];
                    fprintf(file, "Name: %s\n", items->name[i]);
                    fprintf(file, "Price: %.2fR$\n", items->price[i]);
                    fprintf(file, "Total amount in \"%s\": %d\n", items->unit[i], items->qty[i]);
                    fprintf(file, "Price Per Quantity: %.2fR$\n\n", pricePQ);
                }
            
                printf("\nSaved successfully!\n");
        
                fclose(file);
                break;
            }
            case 0:
                return;
                break;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();                
        }
    } while (op != 0);
}

void Credits() {
    Clear();
    int loopCount = 0;
    char *strings[] = {"Made by: Gabriel Oliveira Miranda",
                       "a high school freshman",
                       "this code is still in beta!"};

    while(loopCount != 2) {
        for(int i = 0; i < 3; i++) {
            type(strings[i], 35);
            SleepMS(375);
            delete(strings[i], 25);
        }
        loopCount++;
    }
    printf("You saw all the credits, now we're heading back\n");
}

void readItem(Item *items, int totalItems, char *buff) {
    Clear();
    FILE *file = accessFile("BuySmart.txt", "r");
    int op, typeSpeed = 7;

    do {
        printf("========Read Menu========\n");
        type("[1] Read from file\n[0] Return to main menu\n", typeSpeed);
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
                Clear();
                int fileCount = 0;
                char line[1024];

                printf("Items list:\n\n");

                if(!file) {
                    printf("\nError: %s\n", strerror(errno));
                    Pause();
                    Clear();
                    return;
                }

                while(fgets(line, sizeof(line), file) != NULL && fileCount < MAX_ITEMS) {
                    printf("%s", line);
                }
                Pause();
                Clear();
                break;        
            } 
            case 0: 
                return;
                break;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();                
        }

    } while(op != 0);

    fclose(file);
}

void compareItem(Item *items, int *totalItems, char *buff) {
    Clear();
    int op, typeSpeed = 7;

    Item fileItems = {0};
    int fileCount = 0;

    do {
        printf("========Compare Menu========\n");
        type("[1] Read from file\n[0] Return to main menu\n", typeSpeed);
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

                    while (fgets(line, sizeof(line), file) != NULL && fileCount < MAX_ITEMS) {
                        if (strncmp(line, "Name:", 5) == 0) {
                            sscanf(line, "Name: %49[^\n]", tempName);
                        }
                        else if (strncmp(line, "Price:", 6) == 0) {
                            sscanf(line, "Price: %fR$", &tempPrice);
                        }
                        else if (strncmp(line, "Total amount in", 15) == 0) {
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

                    if (fileCount == 0) {
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

                    if (selectedCount == 0) {
                        printf("\nError: No valid items selected.\n");
                        Pause();
                        Clear();
                        break;
                    }

                    printf("\nSelected items from file with Price per Quantity:\n");

                    float bestPricePQ = 1e9f;
                    int bestIndex = -1;

                    for (int i = 0; i < selectedCount; i++) {
                        int idx = selected[i];
                        if (fileItems.qty[idx] == 0) {
                            printf("- %s: Quantity is zero, cannot calculate price per quantity\n", fileItems.name[idx]);
                            continue;
                        }
                        float pricePQ = fileItems.price[idx] / (float)fileItems.qty[idx];
                        printf("- %s: Price per Quantity = %.2f\n", fileItems.name[idx], pricePQ);

                        if (pricePQ < bestPricePQ) {
                            bestPricePQ = pricePQ;
                            bestIndex = idx;
                        }
                    }

                    if (bestIndex != -1) {
                        printf("\nBest item based on Price per Quantity:\n");
                        printf("-> %s with %.2f per unit\n", fileItems.name[bestIndex], bestPricePQ);
                    } else {
                        printf("\nNo valid items to compare.\n");
                    }

                    Pause();
                    Clear();
                    break;
                }
                case 0:
                    return;
                    break;
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

void registItem(Item *items, int *totalItems, char *buff) {
    Clear();
    int qty, op, typeSpeed = 7;

    do {
        printf("========Register Menu========\n");
        type("[1] Add\n[0] Return to main menu\n", typeSpeed);
        typeSpeed = 0;

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);

        if (sscanf(buff, "%d", &op) != 1) {
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
        
                    if (sscanf(buff, "%d", &qty) != 1 || qty <= 0) {
                        errno = EINVAL; //* Invalid Arguments ERROR;
                        perror("\nError");
                        Pause();
                        Clear();
                        continue;
                    }

                    if (*totalItems + qty > MAX_ITEMS) {
                        printf("\nError: You can only add up to %d items total.\n", MAX_ITEMS);
                        Pause();
                        Clear();
                        continue;
                    }
                } while (qty <= 0);
    
                for (int i = 0; i < qty; i++) {
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

                    printf("\nSuccessfully registered!!\n");
                }
                break;
            case 0:
                return;
                break;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
                
        }
    } while (op != 0);
    Clear();
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
    for (int i = 0; str[i]; i++) {
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

FILE* accessFile(char *fileName, char *act) {
    char filePath[MAX_PATH_LEN];
    getFilePath(filePath, sizeof(filePath), fileName);
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