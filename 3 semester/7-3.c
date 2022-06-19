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
    int n;
    scanf("%d", &n);
    int i = 0;
    int *pid = calloc(n, 4);
    pid[0] = getpid();
    //printf("pid = %d %d", pid[i], i + 1);
    //fflush(stdout);
    int status;
    for (i = 1; i < n; i++) {
        //printf("curpid = %d %d\n", getpid(), i);
        //printf("ipid = %d %d\n", pid[i - 1], i);
        if (pid[i - 1] == getpid()) {
            printf("OUTpid = %d %d\n", pid[i - 1], i);
            pid[i] = fork();
            if (!pid[i]) {
                pid[i] = getpid();
            }
            //printf("pid[%d] = %d\n", i, pid[i]);
            wait(&status);
        }
        for (int j = 0; j < n; j++) {
            //printf("pid[%d] = %d ", j, pid[j]);
        }
        printf("\n");
    }
    if (pid[n - 1] == getpid()) {
        printf("OUTendpid = %d %d\n", getpid(), i);
    }
    //printf("END\n");
    if (pid[0] == getpid()) {
        free(pid);
    }
    return 0;
}
