#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void CleanIn();
double LogBase(double logarithm, double base);

int main() {
    double base, log;

    printf("Enter the logarithm: ");
    scanf("%lf", &log);
    CleanIn();
    
    printf("Enter the base: ");
    scanf("%lf", &base);
    CleanIn();

    printf("Result: %.2lf\n", LogBase(log, base));

    return 0;
}

double LogBase(double logarithm, double base) {
    if(logarithm == 0) 
        return 0;
    
    if(logarithm == base)
        return 1;

    if(base <= 1 || logarithm <= 0)
        return NAN;

    return log(logarithm) / log(base);
}

void CleanIn() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}