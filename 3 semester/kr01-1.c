#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        if (argv[i] && strlen(argv[i])) {
            int len = strlen(argv[i]);
            char flag = 1;
            for (int j = 0; flag && j < len / 2 + 1; j++) {
                if (argv[i][j] != argv[i][len - j - 1]) {
                    flag = 0;
                } else if (!(argv[i][j] >= 'a' && argv[i][j] <= 'z')) {
                    flag = 0;
                }
            }
            if (flag) {
                fputs(argv[i], stdout);
                printf("\n");
            }
        }
    }
    return 0;
}
