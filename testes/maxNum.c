#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#define ARCHIVE "maxNum.txt"
#define MAXNUMS 100000000ULL    //* 10⁸
#define MAXGEN (1ULL << 63)     //* 2⁶³ bytes
//! To generate 10⁸ 64bit numbers and find the max took 18.5s, 1.4gb file, using hdd, i5-4690, 16gb of ram and using Linux 
//! To generate 10⁸ 64bit numbers and find the max took 51s, 1.55gb file, using ssd, i5-4690, 16gb of ram and using Windows 

uint64_t rand64(uint64_t max) {
    uint64_t high = (uint64_t)rand() & 0x7FFF; //* 32767
    uint64_t mid  = (uint64_t)rand() & 0x7FFF;
    uint64_t low  = (uint64_t)rand() & 0x7FFF;
    uint64_t extra = (uint64_t)rand() & 0x7;
    uint64_t num = (high << 33) | (mid << 18) | (low << 3) | extra;
    return num % max + 1;
}

int main(void) {
    FILE *f = fopen(ARCHIVE, "r");
    uint64_t max = 0;
    srand(time(NULL));

    if (!f) {
        f = fopen(ARCHIVE, "w");
        if (!f) {
            perror("Opening file error!!");
            return 1;
        }

        for (uint64_t i = 0; i < MAXNUMS; i++) {
            uint64_t num = rand64(MAXGEN);
            fprintf(f, "%" PRIu64 "\n", num);
            if (num > max)
                max = num;
        }

        fclose(f);
    }

    printf("The biggest number of this .txt is: %" PRIu64 "\n", max);
    return 0;
}
