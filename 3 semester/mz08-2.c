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
    enum
    {
        PROCF = 1,
        PROCS = 2,
        PROCG = 3
    };
    int pids = fork();
    if (pids < 0) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        _exit(1);
    }
    if (pids > 0) {
        int statuss;
        if ((wait(&statuss)) < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(1);
        }
        printf("%d\n", PROCF);
        return 0;
    } else {
        int pidg = fork();
        if (pidg < 0) {
            fprintf(stderr, "fork: %s\n", strerror(errno));
            _exit(1);
        }
        if (pidg > 0) {
            int statusg;
            if ((wait(&statusg)) < 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                _exit(1);
            }
            printf("%d ", PROCS);
        } else {
            printf("%d ", PROCG);
        }
    }
}
