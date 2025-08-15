#include <stdio.h>
#include <string.h>
#include <windows.h>

void getFilePath(char *fullPath, size_t size, const char *fileName);
FILE* accessFile(char *fileName, char *act);

int main() {
    char fileName[50];

    printf("Type-in the file path: ");
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = '\0';

    FILE *file = accessFile(fileName, "r");
    if (file == NULL) {
        printf("\nFile opening error!\n");
        return 1;
    }

    int countChars = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        countChars++;
    }

    fclose(file);

    printf("The file has %d chars.\n", countChars);

    return 0;
}

FILE* accessFile(char *fileName, char *act) {
    char filePath[MAX_PATH];
    getFilePath(filePath, sizeof(filePath), fileName);
    FILE *file = fopen(filePath, act);
    return file;
}

void getFilePath(char *fullPath, size_t size, const char *fileName) { 
    char pathEXE[MAX_PATH];
    GetModuleFileName(NULL, pathEXE, MAX_PATH);

    char* p = strrchr(pathEXE, '\\');
    if (p) {
       *(p + 1) = '\0';
    }

    snprintf(fullPath, size, "%s%s", pathEXE, fileName);
}
