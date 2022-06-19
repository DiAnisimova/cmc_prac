#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const char rights[] = "rwxrwxrwx";
    enum
    {
        N = sizeof(rights) 
    };
    for (int i = 1; i < argc; i++) {
        char newrights[N];
        newrights[N - 1] = '\0'; 
        unsigned int number = 0;
        sscanf(argv[i], "%o", &number);
        for (int j = 1; j < N; j++) { 
            if (number & 1) {
                newrights[N - j - 1] = 0xff;
            } else { 
                newrights[N - j - 1] = 0;
            }
            number >>= 1;
        }
        for (int j = 0; j < N - 1; j++) {
            if (newrights[j] & rights[j]) {
                newrights[j] = rights[j];
            } else {
                newrights[j] = '-';
            }
        }
        fputs(newrights, stdout);
        printf("\n");
    }
    return 0;
}

