#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>

#define MAXCHAR (1ULL << 8)
#define VERSION "b0.2.73"

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #include <shlobj.h>
    #include <initguid.h>
    #include <knownfolders.h>
    #define SYSTEM "Windows"
    #define cls() system("cls")
    #define rmdir _rmdir
    #define chdir _chdir
    #define getcwd _getcwd
    HANDLE hConsole;
#elif defined(__linux__) || defined(__APPLE__) 
    #ifdef __linux__
        #define SYSTEM "Linux"
    #else
        #define SYSTEM "Mac OS"
    #endif

    #include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
    #include <pwd.h>
    #include <limits.h>
    #define cls() system("clear")
#else
    #error "Operational system not recognized, terminating program!!"
#endif


char *get_time(void);
void trim(char *str);
char *get_user(void);
void neofetchCmd(void);
char *get_hostname(void);
void setup_console(void);
void updatehistory(void);
void setColor(int color);
char *get_cpu_model(void);
void rmCmd(char *instruction);
long get_total_ram_mb(void);
void rmdirCmd(char *command);
void mkdirCmd(char *command);
void catCmd(char *instruction);
void lsCmd(const char *address);
void echoCmd(char *instruction);
char *get_default_address(void);
void touchCmd(char *instruction);
char *handle_cd_dash(char *address);
int sort(char **array, size_t count);
ssize_t strchar(const char *str, int chr);
void update_last_directory(char *address);
ssize_t strrchar(const char *str, int chr);
char *strrm(char *str, const char *substr);
void charRm(char *str, int targ, int repl);
void cmdsCommand(const char **cmds, size_t count);
char *cdCmd(const char *instruction, char *address);
char *handle_normal_cd(const char *path, char *address);
char **copyMat(char **dest, const char **src, size_t size);
void printc(const char *str, int color, int resetColor, ...);
void manCmd(const char **cmds, char *instruction, size_t count);

static char *last_directory = NULL;


int main(void) {
#ifdef _WIN32
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    
    const char *cmds[] = {"clear", "exit", "echo", "neofetch", "updatehistory",
                          "cmds", "cd", "ls", "man", "whoami", "date", "pwd",
                          "mkdir", "rmdir", "cat", "touch", "rm"
                         };
    size_t cmdCount = sizeof(cmds) / sizeof(cmds[0]);
    
    char *instruction = calloc(MAXCHAR, sizeof(char));
    
    if (!instruction) {
        perror("ERROR: Memory allocation error!!");
        return 1;
    }
    char *address = get_default_address();
    
    while (true) {
        int found = 0;

        #ifdef _WIN32
            charRm(address, '\\', '/');
        #endif

        printc("%s@%s", 10, 7, get_user(), get_hostname()); // Light Green to White
        putchar(':');
        printc("%s", 11, 7, address); // Light Blue to White
        printf("$ ");

        if (!fgets(instruction, MAXCHAR, stdin)) 
            break;

        trim(instruction);

        instruction[strcspn(instruction, "\n")] = '\0';
        
        if (strlen(instruction) == 0)
            continue;
    

        for (size_t i = 0; i < cmdCount; i++) {
            if (strncmp(instruction, cmds[i], strlen(cmds[i])) == 0) {
                if (strlen(instruction) == strlen(cmds[i]) || instruction[strlen(cmds[i])] == ' ') {
                    found = 1;
                    
                    if (strcmp(cmds[i], cmds[0]) == 0) //* clear instruction
                        cls();
                    else if (strcmp(cmds[i], cmds[1]) == 0) { //* exit instruction
                        free(instruction);
                        free(address);
                        return 0;
                    }
                    else if (strcmp(cmds[i], cmds[2]) == 0) //* echo instruction
                        echoCmd(instruction);
                    else if (strcmp(cmds[i], cmds[3]) == 0) //* neofetch instruction
                        neofetchCmd();
                    else if (strcmp(cmds[i], cmds[4]) == 0) //* updateinfo instruction
                        updatehistory();
                    else if (strcmp(cmds[i], cmds[5]) == 0) //* cmds instruction
                        cmdsCommand(cmds, cmdCount);
                    else if (strcmp(cmds[i], cmds[6]) == 0) { //* cd instruction
                        #ifdef _WIN32
                            charRm(instruction, '/', '\\');
                        #endif
                        char *new_address = cdCmd(instruction, address);
                        free(address); 
                        address = new_address;
                    }
                    else if (strcmp(cmds[i], cmds[7]) == 0) //* ls instruction
                        lsCmd(address);
                    else if (strcmp(cmds[i], cmds[8]) == 0) //* man instruction
                        manCmd(cmds, instruction, cmdCount);
                    else if (strcmp(cmds[i], cmds[9]) == 0) //* whoami instruction
                        printf("%s\n", get_user());
                    else if (strcmp(cmds[i], cmds[10]) ==  0) //* date instruction
                        printf("%s\n", get_time());
                    else if (strcmp(cmds[i], cmds[11]) == 0) //* pwd instruction
                        printf("%s\n", address);
                    else if (strcmp(cmds[i], cmds[12]) == 0) //* mkdir instruction
                        mkdirCmd(instruction);
                    else if (strcmp(cmds[i], cmds[13]) == 0) //* rmdir instruction
                        rmdirCmd(instruction);
                    else if (strcmp(cmds[i], cmds[14]) == 0) //* cat instruction
                        catCmd(instruction);
                    else if (strcmp(cmds[i], cmds[15]) == 0) //* touch instruction
                        touchCmd(instruction);
                    else if (strcmp(cmds[i], cmds[16]) == 0) //* rm instruction
                        rmCmd(instruction);
                    break;
                }
            }
        }
        if (!found)
            printf("The command '%s' was not found!!\n", instruction);
    }

    free(instruction);
    free(address);
    return 0;
}

void rmCmd(char *instruction) {
    instruction = strrm(instruction, "rm");
    trim(instruction);
    char answer[0x20];

    if (instruction[0] == '\0') {
        printf("rm: missing operand\nUse \"man rm\" to check the manual\n");
        return;
    } 

    printf("Are you sure you want to delete this file? (y/n): ");
    if (fgets(answer, sizeof(answer), stdin) == NULL) {
        printf("Error reading input\n");
        return;
    }
    answer[strcspn(answer, "\n")] = '\0';

    if (answer[0] == 'y' || answer[0] == 'Y') {
        if (remove(instruction) != 0) {
            perror("Error");
        } else {
            printf("File '%s' deleted successfully\n", instruction);
        }
    } else {
        printf("Deletion cancelled\n");
    }
}

void touchCmd(char *instruction) {
    instruction = strrm(instruction, "touch");
    trim(instruction);

    if (instruction[0] == '\0') {
        printf("touch: missing operand\nUse \"man touch\" to check the manual\n");
        return;
    }

    FILE *f = fopen(instruction, "w");

    fclose(f);
}

void catCmd(char *instruction) {
    instruction = strrm(instruction, "cat");
    trim(instruction);

    if (instruction[0] == '\0') {
        printf("cat: missing operand\nUse \"man cat\" to check the manual\n");
        return;
    }

    FILE *f = fopen(instruction, "rb");
    if (f == NULL) {
        fprintf(stderr, "Error: couldn't open %s\n", instruction);
        return;
    }
    
    int byte;
    while ((byte = fgetc(f)) != EOF) {
        if (isprint(byte) || byte == '\n' || byte == '\t') {
            putchar(byte);
        } else {
            printf("\\x%02X", byte);
        }
    }
    
    putchar('\n');
    fclose(f);
}

void rmdirCmd(char *command) {
    command = strrm(command, "rmdir");
    trim(command);

    if (command[0] == '\0') {
        printf("rmdir: missing operand\nUse \"man rmdir\" to check the manual\n");
        return;
    }
    if (rmdir(command) != 0)
        perror("Error");
}

void mkdirCmd(char *command) {
    command = strrm(command, "mkdir");
    trim(command);

    if (command[0] == '\0') {
        printf("mkdir: missing operand\nUse \"man mkdir\" to check the manual\n");
        return;
    }
#ifdef _WIN32
    if (_mkdir(command) != 0)
        perror("Error");
#else
    size_t mode = 0777;

    if (mkdir(command, mode) != 0)
        perror("Error");
#endif
}

char *get_user(void) {
#ifdef _WIN32
    char *user = getenv("USERNAME");
#else
    char *user = getenv("USER");
#endif

    return (user) ? user : "Unknown";
}

char *get_hostname(void) {
    static char hostname[256];

#ifdef _WIN32
    DWORD size = sizeof(hostname);
    if (!GetComputerNameA(hostname, &size))
        strcpy(hostname, "Unknown");
#else
    if (gethostname(hostname, sizeof(hostname)) != 0)
        strcpy(hostname, "Unknown");
#endif

    return hostname;
}


void manCmd(const char **cmds, char *instruction, size_t count) {
    instruction = strrm(instruction, "man");
    trim(instruction);
    size_t found = 0;

    for (size_t i = 0; i < count; i++) {
        if (strncmp(instruction, cmds[i], strlen(cmds[i])) == 0) {
            if (strlen(instruction) == strlen(cmds[i]) || instruction[strlen(cmds[i])] == ' ') {
                found = 1;
                
                if (strcmp(cmds[i], cmds[0]) == 0) //* cls or clear instruction
                    printf("\"%s\" clears your terminal's screen and its scrollback buffer\n", cmds[0]);
                else if (strcmp(cmds[i], cmds[1]) == 0) //* exit instruction
                    printf("\"%s\" exit the terminal\n", cmds[1]);
                else if (strcmp(cmds[i], cmds[2]) == 0) //* echo instruction
                    printf("\"%s\" display a line of text\necho [STRING]\n", cmds[2]);
                else if (strcmp(cmds[i], cmds[3]) == 0) //* neofetch instruction
                    printf("\"%s\", a fast and highly customizable system info script\n", cmds[3]);
                else if (strcmp(cmds[i], cmds[4]) == 0) //* updateinfo instruction
                    printf("\"%s\" displays the update history of the terminal\n", cmds[4]);
                else if (strcmp(cmds[i], cmds[5]) == 0) //* cmds instruction
                    printf("\"%s\" displays the list of commands available\n", cmds[5]);
                else if (strcmp(cmds[i], cmds[6]) == 0) //* cd instruction
                    printf("\"%s\" changes the working directory of the terminal\n", cmds[6]);
                else if (strcmp(cmds[i], cmds[7]) == 0) //* ls instruction
                    printf("\"%s\" list directory contents\n", cmds[7]);
                else if (strcmp(cmds[i], cmds[8]) == 0) //* man instruction
                    printf("\"%s\" a interface to the system reference manuals\n", cmds[8]);
                else if (strcmp(cmds[i], cmds[9]) == 0) //* whoami instruction
                    printf("\"%s\" displays the user that you are currently logged-in\n", cmds[9]);
                else if (strcmp(cmds[i], cmds[10]) ==  0) //* date instruction
                    printf("\"%s\" displays the current date and time\n", cmds[10]);
                else if (strcmp(cmds[i], cmds[11]) ==  0) //* pwd instruction
                    printf("\"%s\" displays the current working directory\n", cmds[11]);                
                else if (strcmp(cmds[i], cmds[12]) ==  0) //* mkdir instruction
                    printf("\"%s\" makes directories\nmkdir [FOLDER NAME]\n", cmds[12]);                
                else if (strcmp(cmds[i], cmds[13]) ==  0) //* rmdir instruction
                    printf("\"%s\" removes empty directories\nrmdir [FOLDER NAME]\n", cmds[13]);                
                else if (strcmp(cmds[i], cmds[14]) ==  0) //* rmdir instruction
                    printf("\"%s\" displays the file content\ncat [FILE NAME]\n", cmds[14]);                
                else if (strcmp(cmds[i], cmds[15]) ==  0) //* rmdir instruction
                    printf("\"%s\" creates a file\ntouch [FILE NAME]\n", cmds[15]);                
                else if (strcmp(cmds[i], cmds[16]) ==  0) //* rm instruction
                    printf("\"%s\" removes a file(only files)\nrm [FILE NAME]\n", cmds[16]);                
                break;
            }
        }
    }
    if (!found)
        printf("The manual for the '%s' command was not found!!\n", instruction);
}

char *strrm(char *str, const char *substr) {
    int len = strlen(str);
    int sublen = strlen(substr);
    char *copy = strdup(str);


    if (sublen == 0 || len < sublen)
        return copy;

    for (size_t i = 0; i <= len - sublen; i++) {
        int match = 1;
        for (size_t j = 0; j < sublen; j++) {
            if (copy[i + j] != substr[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            for (size_t k = i; k <= len - sublen; k++) 
                copy[k] = copy[k + sublen];
            break;
        }
    }

    return copy;
}

void trim(char *str) {
    if (str == NULL) return;
    
    size_t spaces = 0;
    while (str[spaces] == ' ') {
        spaces++;
    }
    
    if (spaces == 0) return;
    
    size_t i = 0;
    while (str[spaces + i] != '\0') {
        str[i] = str[spaces + i];
        i++;
    }
    str[i] = '\0';
}

char *cdCmd(const char *instruction, char *address) {
    const char *path = instruction + strlen("cd");
    while (*path == ' ') path++;
    
    if (strcmp(path, "-") == 0) {
        return handle_cd_dash(address);
    }
    
    update_last_directory(address);
    
    return handle_normal_cd(path, address);
}

char *handle_cd_dash(char *address) {
    if (last_directory == NULL) {
        printf("cd: no previous directory\n");
        return strdup(address);
    }
    
    printf("%s\n", last_directory);
    
    if (chdir(last_directory) != 0) {
        perror("cd");
        return "";
    }

    char new_cwd[1024];
    if (getcwd(new_cwd, sizeof(new_cwd)) != NULL) {
        char *temp = last_directory;
        last_directory = strdup(address);
        free(temp);
        return strdup(new_cwd);
    }
    
    return strdup(address);
}

void update_last_directory(char *address) {
    if (last_directory != NULL)
        free(last_directory);

    last_directory = strdup(address);
}

char *handle_normal_cd(const char *path, char *address) {
    char old_cwd[1024];
    if (getcwd(old_cwd, sizeof(old_cwd)) == NULL) {
        strcpy(old_cwd, ".");
    }
    
    if (strlen(path) == 0) {
    #ifdef _WIN32
        const char *home_path = getenv("USERPROFILE");
    #else
        const char *home_path = getenv("HOME");
    #endif
        if (!home_path) return strdup(address);
        
        if (chdir(home_path) == 0) {
            char new_cwd[1024];
            if (getcwd(new_cwd, sizeof(new_cwd)) != NULL && strcmp(old_cwd, new_cwd) != 0) {
                return strdup(new_cwd);
            }
        }
    }
    else if (strcmp(path, "..") == 0) {
        char new_path[1024];
        strncpy(new_path, address, sizeof(new_path) - 1);
        new_path[sizeof(new_path) - 1] = '\0';
        
        char *last_slash = strrchr(new_path, '/');
        if (last_slash != NULL && last_slash != new_path) {
            *last_slash = '\0';
        } else if (last_slash == new_path) {
            new_path[1] = '\0';
        }
        
        if (chdir(new_path) == 0) {
            char new_cwd[1024];
            if (getcwd(new_cwd, sizeof(new_cwd)) != NULL && strcmp(old_cwd, new_cwd) != 0) {
                return strdup(new_cwd);
            }
        }
    }
    else if (strcmp(path, ".") == 0) {
        return strdup(address);
    }
    else if (path[0] == '/') {
        if (chdir(path) == 0) {
            char new_cwd[1024];
            if (getcwd(new_cwd, sizeof(new_cwd)) != NULL && strcmp(old_cwd, new_cwd) != 0) {
                return strdup(new_cwd);
            }
        }
    }
    else {
        char full_path[2048];
        snprintf(full_path, sizeof(full_path), "%s/%s", address, path);
        
        for (char *p = full_path; *p; p++) {
            if (p[0] == '/' && p[1] == '/') {
                memmove(p, p + 1, strlen(p));
            }
        }
        
        if (chdir(full_path) == 0) {
            char new_cwd[1024];
            if (getcwd(new_cwd, sizeof(new_cwd)) != NULL && strcmp(old_cwd, new_cwd) != 0) {
                return strdup(new_cwd);
            }
        }
    }
    
    perror("cd");
    return strdup(address);
}

void charRm(char *str, int targ, int repl) {
    for (size_t i = 0; str[i]; i++) 
        if (str[i] == (char)targ) str[i] = (char)repl;
}

void cmdsCommand(const char **cmds, size_t count) {
    static char **copy = NULL;
    static int initialized = 0;

    if (!initialized) {
        copy = malloc(count * sizeof(char *));
        for (size_t i = 0; i < count; i++)
            copy[i] = strdup(cmds[i]);

        sort(copy, count);
        initialized = 1;
    }

    for (size_t i = 0; i < count; i++)
        printf("%s\n", copy[i]);
}


char **copyMat(char **dest, const char **src, size_t size) {
    dest = malloc(size * sizeof(char *));
    if (!dest) return NULL;

    for (size_t i = 0; i < size; i++) {
        dest[i] = strdup(src[i]);
    }

    return dest;
}

int sort(char **array, size_t count) {
    char *aux;
    int switches = 0;

    for(size_t i = 0; i < count - 1; i++) {
        for(size_t j = 0; j < count - i - 1; j++) {
            if(strcasecmp(array[j], array[j + 1]) > 0) {
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;

                switches = 1;
            }
        }
        if(!switches)
            break;
    }
    return 1;
}

void updatehistory(void) {
    const char *logs[] = {"a0.0.4 - created terminal\n\tAdded: clear, echo and exit command\n\n",
                          "a0.0.55 - minor changes\n\tAdded: neofetch cmd\n\n",
                          "a0.0.75 - minor changes\n\tAdded: commands history\n\n",
                          "a0.0.8 - minor changes\n\tEdited: optimized the sort algorithm\n\n",
                          "a0.0.95 - minor changes\n\tEdited: now the neofetch menu displays the cpu and mem\n\n",
                          "a0.0.975 - minor changes\n\tRemoved: system instruction \n\n",
                          "a0.1.35 - big changes\n\tAdded: cd instruction\n\n",
                          "b0.1.55 - big changes\n\tAdded: ls instruction\n\n",
                          "b0.1.6 - minor changes\n\tAdded: \"initguid.h\" and \"knownfolders.h\" windows libs\n\n",
                          "b0.1.65 - minor changes\n\tEdited: neofetch function\n\n",
                          "b0.1.82 - big changes\n\tAdded: man command and the author of this code\n\n",
                          "b0.2.0 - big changes\n\tEdited: get_time function and neofetch command\n\n",
                          "b0.2.1 - big changes\n\tAdded: date command\n\n",
                          "b0.2.23 - big changes\n\tAdded: pwd command\n\n",
                          "b0.2.34 - big changes\n\tAdded: mkdir and rmdir command\n\n",
                          "b0.2.36 - minor changes\n\tEdited: now neofetch displays the host\n\n",
                          "b0.2.71 - big changes\n\tAdded: cat, touch and rm command\n\n",
                          "b0.2.73 - minor changes(current)\n\tEdited: echo cmd, changed how it works\n"
                        };
    size_t logCount = sizeof(logs) / sizeof(logs[0]);

    for (size_t i = 0; i < logCount; i++)
        printf("%s", logs[i]);
    
}

void echoCmd(char *instruction) {
    instruction = strrm(instruction, "echo");
    trim(instruction);

    size_t init = strchar(instruction, '\"');
    size_t end = strrchar(instruction, '\"');

    if (init == -1 && end == -1) {
        printf("%s\n", instruction);
        return;
    } else {
        for (size_t i = 0; instruction[i]; i++) {
            if (i != (size_t)init && i != (size_t)end) {
                putchar(instruction[i]);
            }
        }
        putchar('\n');
    }
}

ssize_t strchar(const char *str, int chr) {
    if (strlen(str) == 0) return -1;

    for (size_t i = 0; str[i]; i++) 
        if (str[i] == (char)chr) return i;

    return -1;   
}

ssize_t strrchar(const char *str, int chr) {
    size_t len = strlen(str);
    
    if (len == 0) return -1; 
    
    for (size_t i = len - 1; ; i--) {
        if (str[i] == (char)chr) return (ssize_t)i;
        if (i == 0) break;
    }
    return -1;
}
char* get_default_address(void) {
#ifdef _WIN32
    PWSTR path = NULL;
    if (SHGetKnownFolderPath(&FOLDERID_Profile, 0, NULL, &path) == S_OK) {
        char *address = malloc(1024);
        wcstombs(address, path, 1024);
        CoTaskMemFree(path);
        return address;
    }
#else
    char *home = getenv("HOME");
    if (home != NULL) {
        return strdup(home);
    }
    
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL) {
        return strdup(pw->pw_dir);
    }
#endif
    
    return strdup(".");
}

void setColor(int cor) {
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, cor);
#else
    switch(cor) {
        case 2: printf("\033[32m"); break; // Green
        case 4: printf("\033[31m"); break; // Red
        case 6: printf("\033[33m"); break; // Yellow
        case 7: printf("\033[37m"); break; // White
        case 10: printf("\033[92m"); break; // Light Green
        case 11: printf("\033[94m"); break; // Light Blue
        case 12: printf("\033[96m"); break; // Light Cyan
        case 13: printf("\033[91m"); break; // Light Red
        default: printf("\033[0m"); break; // Reset
    }
#endif
} 

void printc(const char *str, int color, int resetColor, ...) {
    setColor(color);

    va_list args;
    va_start(args, resetColor);
    vprintf(str, args);
    va_end(args);

    setColor(resetColor);
}

char *get_time(void) {
    static char buffer[80];
    time_t now;
    struct tm *time_info;

    time(&now);
    time_info = localtime(&now);

    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %z %Y", time_info);
    return buffer;
}


void lsCmd(const char *address) {
#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    
    snprintf(searchPath, sizeof(searchPath), "%s\\*", address);
    hFind = FindFirstFile(searchPath, &findFileData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory\n");
        return;
    }
    
    do {
        if (strcmp(findFileData.cFileName, ".") == 0 || 
            strcmp(findFileData.cFileName, "..") == 0)
            continue;
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);
    
    FindClose(hFind);
    
#else
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(address);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        printf("%s\n", entry->d_name);
    }
    
    closedir(dir);
#endif
}

char *get_cpu_model(void) {
    static char cpu[128];
#ifdef _WIN32
    DWORD size = sizeof(cpu);
    LSTATUS status = RegGetValueA(
        HKEY_LOCAL_MACHINE,
        "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
        "ProcessorNameString",
        RRF_RT_REG_SZ,
        NULL,
        (PVOID)&cpu,
        &size
    );
    if (status != ERROR_SUCCESS)
        return "Unknown";
    return cpu;
#elif __linux__
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) return "Unknown";
    while (fgets(cpu, sizeof(cpu), fp)) {
        if (strncmp(cpu, "model name", 10) == 0) {
            fclose(fp);
            char *colon = strchr(cpu, ':');
            return colon ? colon + 2 : "Unknown";
        }
    }
    fclose(fp);
    return "Unknown";
#elif __APPLE__
    size_t size = sizeof(cpu);
    if (sysctlbyname("machdep.cpu.brand_string", cpu, &size, NULL, 0) == 0)
        return cpu;
    return "Unknown";
#endif
}

long get_total_ram_mb(void) {
#ifdef _WIN32
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status.ullTotalPhys / (1024 * 1024);
#elif __linux__
    long mem_kb = 0;
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return -1;
    fscanf(fp, "MemTotal: %ld kB", &mem_kb);
    fclose(fp);
    return mem_kb / 1024; // MB
#elif __APPLE__
    int64_t mem;
    size_t len = sizeof(mem);
    if (sysctlbyname("hw.memsize", &mem, &len, NULL, 0) == 0)
        return (long)(mem / (1024 * 1024)); // MB
    return -1;
#endif
}

void setup_console(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

void neofetchCmd(void) {
    void setup_console();

#ifdef _WIN32
    const char *ascii_art[] = {
        "/ / / / / / / / / / / / / / / / / / / / / / / / / /",
        " / / / / / / / / / / / / / / / / / / / / / / / / / ",
        "/ / / / / / / / /    ASCII ART    / / / / / / / / /",
        " / / / / / / / / / / / / / / / / / / / / / / / / / ",
        "/ / / / / / / / / / / / / / / / / / / / / / / / / /",
        " / / / / / / / / / / / / / / / / / / / / / / / / / ",
        "",
        "            G A B   O P E R A T I N G   S Y S T E M"
    };
#else
    const char *ascii_art[] = {
        " ██████╗  █████╗ ██████╗           ██████╗ ███████╗",
        "██╔════╝ ██╔══██╗██╔══██╗         ██╔═══██╗██╔════╝",
        "██║  ███╗███████║██████╔╝ ██████  ██║   ██║███████╗",
        "██║   ██║██╔══██║██╔══██╗ ╚═════╝ ██║   ██║╚════██║",
        "╚██████╔╝██║  ██║██████╔╝         ╚██████╔╝███████║",
        " ╚═════╝ ╚═╝  ╚═╝╚═════╝           ╚═════╝ ╚══════╝",
        "",
        "            G A B   O P E R A T I N G   S Y S T E M"
    };
#endif


    size_t lines = sizeof(ascii_art) / sizeof(ascii_art[0]);
    
    int title_color = 6;   // Yellow
    int label_color = 12;   // Light Cyan on linux, Light red on Windows 
    int value_color = 7;    // White
    int art_color = 2;      // Green

#ifdef _WIN32
    label_color = 11;
#endif

    printf("\n");
    
    setColor(art_color);
    for (int i = 0; i < lines; i++) {
        printf("%s\n", ascii_art[i]);
    }
    
#ifdef _WIN32
    printc("===============================\n", 6, 7);
#else
    printc("═══════════════════════════════\n", 6, 7);
#endif
    
    printc("SYSTEM", title_color, 7);
    printf("\n");
    
    printc("OS: ", label_color, 7);
    printf("%s\n", SYSTEM);

#ifdef _WIN32
    printc("-------------------------------\n", 6, 7);
#else
    printc("───────────────────────────────\n", 6, 7);
#endif
    
    printc("INFO", title_color, 7);
    printf("\n");
    
    printc("USER: ", label_color, 7);
    printc("%s\n", value_color, 7, get_user());

    printc("HOST: ", label_color, 7);
    printf("%s\n", get_hostname());

    printc("DATE: ", label_color, 7);
    printf("%s\n", get_time());

#ifdef _WIN32
    printc("-------------------------------\n", 6, 7);
#else
    printc("───────────────────────────────\n", 6, 7);
#endif

    printc("TERMINAL\n", title_color, 7);

    printc("VERSION: ", label_color, 7);
    printf("%s\n", VERSION);

    printc("AUTHOR: ", label_color, 7);
    printf("Gabriel Oliveira Miranda\n");

#ifdef _WIN32
    printc("-------------------------------\n", 6, 7);
#else
    printc("───────────────────────────────\n", 6, 7);
#endif

    printc("SPECS\n", title_color, 7);

    printc("CPU: ", label_color, 7);
    printf("%s", get_cpu_model());

#ifdef _WIN32
    printf("\n");
#endif

    printc("Memory: ", label_color, 7);
    printf("%ldMib\n", get_total_ram_mb());

#ifdef _WIN32
    printc("===============================\n", 6, 7);
#else
    printc("═══════════════════════════════\n", 6, 7);
#endif
}