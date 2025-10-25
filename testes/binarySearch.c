#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXCHAR (1ULL << 6)


typedef struct {
    int *data;
    int size;
} intArr;


int randint(int init, int end);
intArr range(int start, int end);
int binarySearch(intArr list, int targ);
int input(char *buffer, size_t size, const char *fmt, void *out);

int main(void) {
    int n = 0, target;
    char *buffer = calloc(MAXCHAR, sizeof(char)), *str = NULL; 

    while (true) {
        printf("Enter the size of the list: ");
        input(buffer, MAXCHAR, "%d", &n);
    
        if (n <= 0) {
            printf("The quantity has to be greater than 0!!\n");
            continue;
        }
    
        printf("Enter the search value: ");
        input(buffer, MAXCHAR, "%d", &target);
    
        intArr array = range(1, n);

        float logValue = log2f((float)n);
        int maxSteps = ceil(logValue);
        printf("\nlog2(%d) = %.4f\n", n, logValue);
        printf("Theoretical max steps (ceil): %d\n", maxSteps);

        binarySearch(array, target);

        break;
    }

    return 0;
}


int randint(int init, int end) {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    return (rand() % (end - init + 1)) + init;
}

int binarySearch(intArr list, int targ) {
    int init = 0, end = list.size - 1;
    int cmps = 0;

    printf("\nSearching %d in %d elements:\n", targ, list.size);

    while (init <= end) {
        int middle = (init + end) / 2;
        cmps++;
        printf("\nStep %d: start=%d, end=%d, middle=%d, value=%d", cmps, init, end, middle, list.data[middle]);

        if (list.data[middle] == targ) {
            printf("\n\nTarget %d found at the %d-th index in %d comparisons.\n", targ, middle, cmps);
            return middle;

        } else if (list.data[middle] < targ) 
            init = middle + 1;
            
        else
            end = middle - 1;
        
    }

    printf("\n\nTarget %d not found after %d comparisons.", targ, cmps);
    return -1;

}

intArr range(int start, int end) {
    intArr arr;
    arr.size = end;
    arr.data = malloc(arr.size * sizeof(int));

    if (!arr.data) {
        arr.size = 0;
        return arr;
    }

    arr.data[0] = start;

    int sum = 0;
    for (int i = 1; i < arr.size; i++) {
        int n = randint(1, 6);
        arr.data[i] = arr.data[i - 1] + n;
        sum += n;
    }

    printf("\nThe difference average between each numbers in the array: %.2f\n", (float)sum / arr.size);

    return arr;
}

int input(char *buffer, size_t size, const char *fmt, void *out) {
    while (1) {
        if (!fgets(buffer, size, stdin))
            return 0;
    
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(fmt, "%s") == 0) {
            strcpy(out, buffer);
            return 1;
        } 
        else if (sscanf(buffer, fmt, out) == 1)
            return 1;
        
        else
            printf("Invalid input, try again: ");
    
    }
}