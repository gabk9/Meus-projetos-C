#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define Clear() system("cls")
    #define Pause() system("pause")
    #define SleepMS(ms) Sleep(ms)
#else 
    #include <unistd.h>
    #define Clear() system("clear")
    #define Pause() do { \
        printf("\nPress ENTER to continue..."); \
        getchar(); \
    } while(0)
    #define SleepMS(ms) usleep((ms) * 1000)
#endif


#define MAX_CHAR 50
#define MAX_ITEMS 100
#define MAX_FILE_ITEMS 100


typedef struct {
    float price[MAX_ITEMS];
    int qty[MAX_ITEMS];
    char name[MAX_ITEMS][MAX_CHAR];
} Item;


void CleanIn();
void Vload(int ms);
void CleanStr(char *var);
void type(char *text, int ms);
void saveItem(Item *items, int totalItems);
void readItem(Item *items, int totalItems, char *buff);
FILE* accessFile(char *fileName, char *act);
void registItem(Item *items, int *totalItems, char *buff);
void compareItem(Item *items, int *totalItems, char *buff);
void getFilePath(char *fullPath, size_t size, const char *fileName); //! it wasn't me who did this


int main(int argc, char **argv) {
    int op, MLoaded = 0;
    char *buff = (char *)calloc(MAX_CHAR, sizeof(char));
    
    memset(buff, 0, MAX_CHAR);

    if (!buff) {
        printf("\nError: Allocation error!\n");
        return 1;
    }

#ifdef _WIN32
    printf("Running on Windows!!\n");
#else
    printf("Running on Linux!!\n");
#endif

    Vload(20);
    Clear();

    Item items = {0};
    int totalItems = 0;

    do {
        printf("\n========BuySmart========\n");
        if(!MLoaded) {
            type("[1] Register an item\n[2] Compare items\n[3] Save items\n[4] List items\n[5] Search items\n[6] Edit item\n[7] Remove item\n[0] Exit program\n", 2);
            MLoaded = 1;
        } else {
            printf("[1] Register an item\n[2] Compare items\n[3] Save items\n[4] List items\n[5] Search items\n[6] Edit item\n[7] Remove item\n[0] Exit program\n");
        }
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
                saveItem(&items, totalItems);
                Pause();
                break;
            case 4:
                readItem(&items, totalItems, buff);
                Pause();
                break;
            case 5:
                // TODO: Implement search items
                printf("\"Search items\" not implemented yet.\n");
                Pause();
                break;
            case 6:
                // TODO: Implement edit item
                printf("\"Edit item\" not implemented yet.\n");
                Pause();
                break;
            case 7:
                // TODO: Implement remove item
                printf("\"Remove\" item not implemented yet.\n");
                Pause();
                break;
            case 0:
                printf("\nClosing program, Bye!!\n");
                goto leave; //* I'm usig goto because why not LOL
                break;
            default:
                errno = EPERM; //* Operation not permited ERROR
                perror("\nError");
                Pause();
                Clear();
        }

        Clear();

    } while(op != 0);

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

void saveItem(Item *items, int totalItems) {
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
        fprintf(file, "Quantity: %d\n", items->qty[i]);
        fprintf(file, "Price Per Quantity: %.2fR$\n\n", pricePQ);
    }

    printf("\nSaved successfully!\n");

    fclose(file);
}

void readItem(Item *items, int totalItems, char *buff) {
    Clear();
    FILE *file = accessFile("BuySmart.txt", "r");
    int op, Rloaded = 0;

    do {
        printf("\n========Read Menu========\n");
        if(!Rloaded) {
            type("[1] Read from file\n[2] Read recently added\n[0] Return to main menu\n", 7);
            Rloaded = 1;
        } else {
            printf("[1] Read from file\n[2] Read recently added\n[0] Return to main menu\n");
        }
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
            case 2:
                if(!totalItems) {
                    printf("\nError: No recently added items.\n");
                } else {
                    Clear();
                    printf("Items list:\n");
                    for(int i = 0; i < totalItems; i++) {
                        float pricePQ = items->price[i] / (float)items->qty[i];
                        printf("Name: %s\n", items->name[i]);
                        printf("Price: %.2f\n", items->price[i]);
                        printf("Quantity: %d\n", items->qty[i]);
                        printf("Price Per Quantity: %.2f\n\n", pricePQ);
                    }
                }
                Pause();
                Clear();
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

    } while(op != 0);

    fclose(file);
}

void compareItem(Item *items, int *totalItems, char *buff) {
    Clear();
    int op, Cloaded = 0;

    Item fileItems = {0};
    int fileCount = 0;

    do {
        printf("\n========Compare========\n");

        if(!Cloaded) {
            type("[1] Read from file\n[2] Read recently added\n[0] Return to main menu\n", 7);
            Cloaded = 1;
        } else {
            printf("[1] Read from file\n[2] Read recently added\n[0] Return to main menu\n");
        }

        printf("Choose an option: ");
        fgets(buff, MAX_CHAR, stdin);
        CleanStr(buff);

        if(sscanf(buff, "%d", &op) == 1) {
            switch(op) {
                case 1: {
                    FILE *file = accessFile("BuySmart.txt", "r");

                    if (!file) {
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
                        } else if (strncmp(line, "Price:", 6) == 0) {
                            sscanf(line, "Price: %f", &tempPrice);
                        } else if (strncmp(line, "Quantity:", 9) == 0) {
                            sscanf(line, "Quantity: %d", &tempQty);

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
                case 2: {
                    if (*totalItems == 0) {
                        printf("\nError: No recently added items.\n");
                        Pause();
                        Clear();
                        break;
                    }

                    printf("\nRecently added items:\n");
                    for (int i = 0; i < *totalItems; i++) {
                        printf("[%d] %s\n", i + 1, items->name[i]);
                    }

                    printf("\nSelect items to compare by number (e.g. 1 2 4): ");
                    fgets(buff, MAX_CHAR, stdin);
                    CleanStr(buff);

                    int selected[MAX_ITEMS];
                    int selectedCount = 0;
                    char *token = strtok(buff, " ");
                    while(token != NULL && selectedCount < MAX_ITEMS) {
                        int idx = atoi(token);
                        if (idx >= 1 && idx <= *totalItems) {
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

                    printf("\nSelected recently added items with Price per Quantity:\n");

                    float bestPricePQ = 1e9f;
                    int bestIndex = -1;

                    for (int i = 0; i < selectedCount; i++) {
                        int idx = selected[i];
                        if (items->qty[idx] == 0) {
                            printf("- %s: Quantity is zero, cannot calculate price per quantity\n", items->name[idx]);
                            continue;
                        }
                        float pricePQ = items->price[idx] / (float)items->qty[idx];
                        printf("- %s: Price per Quantity = %.2f\n", items->name[idx], pricePQ);

                        if (pricePQ < bestPricePQ) {
                            bestPricePQ = pricePQ;
                            bestIndex = idx;
                        }
                    }

                    if (bestIndex != -1) {
                        printf("\nBest item based on Price per Quantity:\n");
                        printf("-> %s with %.2f per unit\n", items->name[bestIndex], bestPricePQ);
                    } else {
                        printf("\nNo valid items to compare.\n");
                    }

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
    int qty;

    do {
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

        break;
    } while (1);

    for (int i = 0; i < qty; i++) {
        printf("\nName of the Item n%d: ", *totalItems + 1);
        fgets(items->name[*totalItems], MAX_CHAR, stdin);
        CleanStr(items->name[*totalItems]);

        printf("Price in R$: ");
        fgets(buff, MAX_CHAR, stdin);
        sscanf(buff, "%f", &items->price[*totalItems]);
        
        printf("Quantity: ");
        fgets(buff, MAX_CHAR, stdin);
        sscanf(buff, "%d", &items->qty[*totalItems]);

        (*totalItems)++;
    }
}

void CleanStr(char *var) {
    var[strcspn(var, "\n")] = '\0';
}

void CleanIn() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void type(char *text, int ms) {
    for(int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        SleepMS(ms);
    }
}

FILE* accessFile(char *fileName, char *act) {
    char filePath[MAX_PATH];
    getFilePath(filePath, sizeof(filePath), fileName);
    FILE *file = fopen(filePath, act);
    return file;
}

void getFilePath(char *fullPath, size_t size, const char *fileName) { //! it wasn't me who did this
#ifdef _WIN32
    char pathEXE[MAX_PATH];
    GetModuleFileName(NULL, pathEXE, MAX_PATH);

    char* p = strrchr(pathEXE, '\\');
    if (p) {
       *(p + 1) = '\0';
    }

    snprintf(fullPath, size, "%s%s", pathEXE, fileName);
#else

    snprintf(fullPath, size, "./%s", fileName);
#endif
}