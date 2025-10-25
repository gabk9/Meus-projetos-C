#include <stdio.h>
#include <errno.h>

int main() {
    FILE *f = fopen("non_existing_file.txt", "r");
    
    if (f == NULL) {
        perror("Error on opening the file!");
    }
    
    errno = EACCES;
    
    perror("Simulated error");

    return 0;
}
