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
        STR = 9,
        N = 3
    };
    char str[N][STR] = { 0 };
    for (int i = 0; i < N; i++) {
        read(0, str[i], sizeof(str[i]) - 1);
    }
    int pid[N] = { 0 };
    pid[0] = fork();
    if (pid[0] < 0) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        _exit(1);
    }
    for (int i = 1; i < N; i++) {
        if (pid[i - 1] > 0) {
            pid[i] = fork();
            if (pid[i] < 0) {
                fprintf(stderr, "fork: %s\n", strerror(errno));
                _exit(1);
            }
        }
    }
    char flag = 1;
    for (int i = 0; i < N; i++) {
        if (!pid[i]) {
            flag = 0;
        }
    }
    if (flag) {
        int status;
        for (int i = 0; i < N; i++) {
            wait(&status);
        }
        return 0;
    }
    for (int i = 0; i < N; i++) {
        if (!pid[i]) {
            int number = 0;
            if ((sscanf(str[i], "%d", &number)) != 1) {
                fprintf(stderr, "%s\n", strerror(errno));
                _exit(1);
            }
            printf("%d %d\n", i + 1, number * number);
            fflush(stdout);
            break;
        }
    }
}

