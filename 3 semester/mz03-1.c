#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    long long sump = 0;
    long long sumn = 0;
    for (int i = 1; i < argc; i++) {
        int number;
        sscanf(argv[i], "%d", &number);
        if (number > 0) {
            sump += number;
        } else {
            sumn += number;
        }
    }
    printf("%lld\n%lld\n", sump, sumn);
    return 0;
}

