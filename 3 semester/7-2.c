#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

int main(void)
{
    setbuf(stdout, NULL);
    enum
    {
        BUFSIZE = 9,
        FIRST = 1,
        SECOND = 2,
        THIRD = 3
    };
    int count = 0;
    char str1[BUFSIZE];
    char str2[BUFSIZE];
    char str3[BUFSIZE];
    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);
    fgets(str3, sizeof(str3), stdin);
    count++;
    int pid1 = fork();
    int pid2 = 0;
    int pid3 = 0;
    if (pid1 > 0) {
        pid2 = fork();
        if (pid2 > 0) {
            pid3 = fork();
        }
    }
    if (pid1 < 0) {
        _exit(1);// exit(1)?
    }
    if (pid2 < 0) {
        _exit(1);
    }
    if (pid3 < 0) {
        _exit(1);
    }
    if (!pid1) {
        int n1;
        if ((sscanf(str1, "%d", &n1)) != 1) {
            _exit(1); // exit(1)?
        }

        printf("%d %d\n", FIRST, n1 * n1);
    } else if (!pid2) {
        int n2;
        if ((sscanf(str2, "%d", &n2)) != 1) {
            _exit(1); // exit(1)?
        }
        printf("%d %d\n", SECOND, n2 * n2);
    } else if (!pid3) {
        int n3;
        if ((sscanf(str3, "%d", &n3)) != 1) {
           _exit(1); // exit(1)?
        }
        printf("%d %d\n", THIRD, n3 * n3);
    } else {
        int status;
        wait(&status);
        wait(&status);
        wait(&status);
    }
    return 0;
}
