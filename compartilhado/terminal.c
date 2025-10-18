#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#define MAXCHAR (1ULL << 8)
#define CLEAR "clear"
#define ECHO "echo"
#define EXIT "exit"
#define NEOFETCH "neofetch"
#define UPDATEHISTORY "updatehistory"
#define CMDS "cmds"
#define CD "cd"
#define LS "ls"

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #include <shlobj.h>
    #define SYSTEM "Windows"
    #define cls() system("cls")
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


void trim(char *str);
void neofetchCmd(void);
void updatehistory(void);
void setColor(int color);
char *get_cpu_model(void);
long get_total_ram_mb(void);
void lsCmd(const char *address);
void echoCmd(char *instruction);
char* get_default_address(void);
char *handle_cd_dash(char *address);
int sort(char **array, size_t count);
void update_last_directory(char *address);
void charRm(char *str, char targ, char repl);
void cmdsCommand(const char **cmds, size_t count);
char *cdCmd(const char *instruction, char *address);
char *handle_normal_cd(const char *path, char *address);
char **copyMat(char **dest, const char **src, size_t size);
void printc(const char *str, int color, int resetColor, ...);

static char *last_directory = NULL;


int main(void) {
    #ifdef _WIN32
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    
    const char *cmds[] = {CLEAR, EXIT, ECHO, NEOFETCH, UPDATEHISTORY, CMDS, CD, LS};
    size_t cmdCount = sizeof(cmds) / sizeof(cmds[0]);
    
    char *instruction = calloc(MAXCHAR, sizeof(char));
    
    if (!instruction) {
        perror("ERROR: Memory allocation error!!");
        return 1;
    }
    char *address = get_default_address();
    
    while (true) {
        int found = 0;

        printc("terminal", 10, 7); // Light Green to White
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
                    
                    if (strcmp(cmds[i], CLEAR) == 0) //* cls or clear instruction
                        cls();
                    else if (strcmp(cmds[i], EXIT) == 0) { //* exit instruction
                        free(instruction);
                        free(address);
                        return 0;
                    }
                    else if (strcmp(cmds[i], ECHO) == 0) //* echo instruction
                        echoCmd(instruction);
                    else if (strcmp(cmds[i], NEOFETCH) == 0) //* neofetch instruction
                        neofetchCmd();
                    else if (strcmp(cmds[i], UPDATEHISTORY) == 0) //* updateinfo instruction
                        updatehistory();
                    else if (strcmp(cmds[i], CMDS) == 0) //* cmds instruction
                        cmdsCommand(cmds, cmdCount);
                    else if (strcmp(cmds[i], CD) == 0) { //* cd instruction
                        char *new_address = cdCmd(instruction, address);
                        free(address); 
                        address = new_address;
                    }
                    else if (strcmp(cmds[i], LS) == 0) //* ls instruction
                        lsCmd(address);
                    break;
                }
            }
        }
        if (!found)
            printf("The instruction '%s' was not found!!\n", instruction);
    }

    free(instruction);
    free(address);
    return 0;
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
    const char *path = instruction + strlen(CD);
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
    
    if (chdir(last_directory) == 0) {
        char new_cwd[1024];
        if (getcwd(new_cwd, sizeof(new_cwd)) != NULL) {
            char *temp = last_directory;
            last_directory = strdup(address);
            free(temp);
            return strdup(new_cwd);
        }
    } else {
        perror("cd");
    }
    return strdup(address);
}

void update_last_directory(char *address) {
    if (last_directory != NULL) {
        free(last_directory);
    }
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

void charRm(char *str, char targ, char repl) {
    for (size_t i = 0; str[i]; i++) 
        if (str[i] == targ) str[i] = repl;
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
    const char *logs[] = {"a0.0.4 - created terminal\n\tAdded: clear, echo, exit\n\n",
                          "a0.0.55 - minor changes\n\tAdded: neofetch cmd\n\n",
                          "a0.0.75 - minor changes\n\tAdded: commands history\n\n",
                          "a0.0.8 - minor changes\n\tEdited: optimized the sort algorithm\n\n",
                          "a0.0.95 - minor changes\n\tEdited: now the neofetch menu displays the cpu and mem\n\n",
                          "a0.0.975 - minor changes\n\tRemoved: system instruction \n\n",
                          "a0.1.35 - big changes\n\tAdded: cd instruction\n\n",
                          "b0.1.55 - big changes(current)\n\tAdded: ls instruction\n"};
    size_t logCount = sizeof(logs) / sizeof(logs[0]);

    for (size_t i = 0; i < logCount; i++)
        printf("%s", logs[i]);
    
}

void echoCmd(char *instruction) {
    if (strlen(instruction) > 4) {
        char *texto = instruction + 4;

        while (*texto == ' ') texto++;

        if (*texto == '"') {
            texto++;
            
            for (size_t i = 0; texto[i]; i++) {
                if (texto[i] == '"')
                    break;
                putchar(texto[i]);
            }
        } else
            printf("%s", texto);
        printf("\n");
    } else
        printf("\n");
}


char* get_default_address(void) {
    #ifdef _WIN32
        PWSTR path = NULL;
        if (SHGetKnownFolderPath(&FOLDERID_Profile, 0, NULL, &path) == S_OK) {
            char *address = malloc(1024);
            wcstombs(address, path, 1024);
            charRm(address, '\\', '/');
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

char* get_time(void) {
    static char buffer[80];
    time_t now;
    struct tm *time_info;
    
    time(&now);
    time_info = localtime(&now);
    
    strftime(buffer, sizeof(buffer), "%m/%d/%Y %H:%M:%S", time_info);
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

void neofetchCmd(void) {
    const char* ascii_art[] = {
        " ██████╗  █████╗ ██████╗           ██████╗ ███████╗",
        "██╔════╝ ██╔══██╗██╔══██╗         ██╔═══██╗██╔════╝",
        "██║  ███╗███████║██████╔╝ ██████  ██║   ██║███████╗",
        "██║   ██║██╔══██║██╔══██╗ ╚═════╝ ██║   ██║╚════██║",
        "╚██████╔╝██║  ██║██████╔╝         ╚██████╔╝███████║",
        " ╚═════╝ ╚═╝  ╚═╝╚═════╝           ╚═════╝ ╚══════╝",
        ""
    };
    
    int title_color = 6;    // Yellow
    int label_color = 12;   // Light Cyan  
    int value_color = 7;    // White
    int art_color = 2;      // Green
    
    printf("\n");
    
    setColor(art_color);
    for (int i = 0; i < 7; i++) {
        printf("%s\n", ascii_art[i]);
    }
    
    printc("═══════════════════════════════\n", 6, 7);
    
    printc("SYSTEM", title_color, 7);
    printf("\n");
    
    printc("OS: ", label_color, 7);
    printf("%s\n", SYSTEM);

    printc("───────────────────────────────\n", 6, 7);
    
    printc("INFO", title_color, 7);
    printf("\n");
    
    printc("USER: ", label_color, 7);
    
#ifdef _WIN32
    char *user = getenv("USERNAME");
#else
    char *user = getenv("USER");
#endif
    if (user) {
        printc("%s\n", value_color, 7, user);
    } else {
        printc("Unknown\n", value_color, 7);
    }

    printc("DATE: ", label_color, 7);
    printf("%s\n", get_time());

    printc("───────────────────────────────\n", 6, 7);

    printc("TERMINAL\n", title_color, 7);

    printc("VERSION: ", label_color, 7);
    printf("b0.1.55\n");

    printc("───────────────────────────────\n", 6, 7);

    printc("SPECS\n", title_color, 7);

    printc("CPU: ", label_color, 7);
    printf("%s", get_cpu_model());

    printc("Memory: ", label_color, 7);
    printf("%ldMib\n", get_total_ram_mb());

    printc("═══════════════════════════════\n", 6, 7);
}