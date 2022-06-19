#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>
#include <sys/wait.h>
#include <limits.h>

int 
sum(int64_t number)
{
    int k = 0;
    uint64_t unum = (uint64_t)number;
    if (unum > LLONG_MIN) {
        unum = -unum;
    }
    while (unum) {
        k = k + unum % 4;
        unum /= 4;
    }
    return k;
}

int main(int argc, char **argv)
{
    int *pids = calloc(argc, sizeof(*pids));
    for (int i = 1; i < argc; i++) {
        pids[i - 1] = fork();
        if (pids[i - 1] < 0) {
            _exit(-1);
        }
        if (!pids[i - 1]) {
            free(pids);
            int64_t number;
            sscanf(argv[i], "%" SCNi64, &number);
            int k = sum(number);
            _exit(k);
        }
    }
    for (int i = 1; i < argc; i++) {
        int status;
        waitpid(pids[i - 1], &status, 0);
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) != -1) {
                printf("%d\n", WEXITSTATUS(status));
                fflush(stdout);
            }
        }
    }
    free(pids);
    _exit(0);
}
