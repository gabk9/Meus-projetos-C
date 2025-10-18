#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>

#define MAXCHAR (1ULL << 8)
#define CLEAR "clear"
#define ECHO "echo"
#define EXIT "exit"
#define NEOFETCH "neofetch"
#define SYSCMD "system"
#define UPDATEHISTORY "updatehistory"

#ifdef _WIN32
    #include <windows.h>
    #include <shlobj.h>
    #define SYSTEM "Windows"
    #define cls() system("cls")
    HANDLE hConsole;
#elif defined(__linux__) || defined(__APPLE__) 
    #ifdef __linux__
        #define SYSTEM "Linux"
    #else
        #define SYSTEM "Mac OS"
    #endif

    #include <unistd.h>
    #include <pwd.h>
    #include <limits.h>
    #define cls() system("clear")
#else
    #error "Operational system not recognized, terminating program!!"
#endif


void updatehistory(void);
void neofetchCmd(void);
void setColor(int color);
void echoCmd(char *command);
char* get_default_address(void);
void printc(const char *str, int color, int resetColor, ...);


int main(void) {
    #ifdef _WIN32
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    
    const char *cmds[] = {CLEAR, EXIT, ECHO, SYSCMD, NEOFETCH, UPDATEHISTORY};
    size_t cmdCount = sizeof(cmds) / sizeof(cmds[0]);
    
    char *command = calloc(MAXCHAR, sizeof(char));
    
    if (!command) {
        perror("ERROR: Memory allocation error!!");
        return 1;
    }
    
    while (true) {
        int found = 0;

        printc("%s: ", 10, 7, get_default_address());

        if (!fgets(command, MAXCHAR, stdin)) 
            break;

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0)
            continue;
    

        for (size_t i = 0; i < cmdCount; i++) {
            if (strncmp(command, cmds[i], strlen(cmds[i])) == 0) {
                if (strlen(command) == strlen(cmds[i]) || command[strlen(cmds[i])] == ' ') {
                    found = 1;
                    
                    if (strcmp(cmds[i], CLEAR) == 0) //* cls or clear cmd
                        cls();
                    else if (strcmp(cmds[i], EXIT) == 0) { //* exit cmd
                        free(command);
                        return 0;
                    }
                    else if (strcmp(cmds[i], ECHO) == 0) //* echo cmd
                        echoCmd(command);
                    else if (strcmp(cmds[i], SYSCMD) == 0) //* system cmd
                        printf("Running on %s\n", SYSTEM);
                    else if (strcmp(cmds[i], NEOFETCH) == 0) //* neofetch cmd'
                        neofetchCmd();
                    else if (strcmp(cmds[i], UPDATEHISTORY) == 0) //* updateinfo cmd
                        updatehistory();
                    break;
                }
            }
        }
        if (!found)
            printf("The command '%s' was not found!!\n", command);
    }

    free(command);
    return 0;
}   

void updatehistory(void) {
    const char *logs[] = {"a0.0.4 - created terminal\n\tAdded: clear, echo, exit\n", "a0.0.55 - current\n\tAdded: neofetch cmd\n"};
    int logCount = sizeof(logs) / sizeof(logs[0]);

    for (size_t i = 0; i < logCount; i++)
        printf("%s", logs[i]);
    
}

void echoCmd(char *command) {
    if (strlen(command) > 4) {
        char *texto = command + 4;

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
    static char address[1024];
    
    #ifdef _WIN32
        PWSTR path = NULL;
        if (SHGetKnownFolderPath(&FOLDERID_Profile, 0, NULL, &path) == S_OK) {
            wcstombs(address, path, sizeof(address));
            CoTaskMemFree(path);
            return address;
        }
    #else
        char *home = getenv("HOME");
        if (home != NULL) {
            strncpy(address, home, sizeof(address) - 1);
            return address;
        }
        
        struct passwd *pw = getpwuid(getuid());
        if (pw != NULL) {
            strncpy(address, pw->pw_dir, sizeof(address) - 1);
            return address;
        }
    #endif
    
    strcpy(address, ".");
    return address;
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
        case 11: printf("\033[96m"); break; // Light Cyan
        case 12: printf("\033[91m"); break; // Light Red
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
    int label_color = 11;   // Light cyan  
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
    printf("a0.0.55\n");
    
    printc("═══════════════════════════════\n", 6, 7);
}