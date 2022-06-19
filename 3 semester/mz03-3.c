#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    enum
    {
        CHANGES = 2, // номер аргумента командной строки, начиная с которого идут изменения
        ROUNDING = 10000 // используется при округлении; 10^4 - т.к. нужны 4 цифры после запятой
    };
    double rate;
    sscanf(argv[1], "%lf", &rate);
    for (int i = CHANGES; i < argc; i++) {
        double change;
        sscanf(argv[i], "%lf", &change);
        rate *= (1 + change / 100);
        rate = round(rate * ROUNDING) / ROUNDING; 
    }
    printf("%.4lf\n", rate);
    return 0;
}


