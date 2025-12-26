#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <inttypes.h>

#ifdef _WIN32
    #include <direct.h>
    #define cls(void) system("cls")
#else
    #include <unistd.h>
    #define cls(void) system("clear")
#endif

#define MAX_ARGS 0x20
#define I_NAN (uint32_t)-1
#define U_NAN (uint64_t)-1
#define MAX_CHAR (1ULL << 10)

char randChr(void);
char *get_user(void);
void trim(char *str);
void initRandom(void);
char *charNumber(void);
char *linesNumber(void);
char *linesNumber(void);
void trimEnd(char *str);
char *getBasePath(void);
void setup_console(void);
char *get_hostname(void);
char *get_time(char *fmt);
double parse_len(char *s);
char *get_cpu_model(void);
void sleepF(double seconds);
bool isBin(const char *str);
bool isHex(const char *str);
bool isOct(const char *str);
void setColor(int8_t color);
void trimBetween(char *str);
char *myDirname(char *path);
void echoHandler(char *str);
bool isValidFile(char *file);
void enableAnsiIfNeeded(void);
char *revStr(const char *str);
char *extractPath(char **str);
void removeComments(char *str);
bool isalldigit(const char *s);
int8_t isDir(const char *path);
uint64_t get_total_ram_mb(void);
char *get_default_address(void);
void safe_lower_inplace(char *s);
char *buildAliasPath(char *path);
char *tolowerstr(const char *str);
void charRm(char *str, int8_t targ);
char *handle_cd_dash(char *address);
char *find_andand_outside_quotes(char *s);
void update_last_directory(char *address);
uint8_t sort(char **array, uint16_t count);
char *strrm(char *str, const char *substr);
char *findFirstEqualOutsideQuotes(char *s);
double eval(char *operation, bool mathlib);
uint8_t is_pi_or_e_expression(const char *s);
int16_t strchar(const char *str, int8_t chr);
int16_t strrchar(const char *str, int8_t chr);
bool isValidBcCommand(char *str, char *command);
char *defaultAddressReplace(const char *address);
uint16_t countIndex(const char *str, int8_t chr);
void createShortcut(char *instruction, char *path);
char **parseData(const char *str, uint16_t *count);
void charReplace(char *str, int8_t targ, int8_t repl);
uint8_t myStrcasestr(const char *str, const char *sub);
uint16_t CountSubStr(const char *str, const char *sub);
char *handle_normal_cd(const char *path, char *address);
double parse_hex_pi_e_bin(const char *str, int16_t *ok);
char **copyMat(char **dest, const char **src, uint16_t size);
void printc(const char *str, int8_t color, int8_t resetColor, ...);
const char *strcasestr_ptr(const char *haystack, const char *needle);
void split_instruction_args(char *line, char **out_cmd, char **out_args);
void printTarg(const char *str, const char *targ, int8_t markColor, int8_t ignoreCase);
int16_t find_main_operator_full(const char *s, const char **multiOps, const char *uniOps, char *foundOp);
void GetProjDir(char *program_root, uint16_t root_size, char *data_folder, uint16_t data_size, char *history_path, uint16_t hist_size);
bool isalias(char *operation, char *args, const char **cmds, uint16_t cmdCount, char **address, char *history_path, char *data_folder, uint16_t isInsideBash);

#endif