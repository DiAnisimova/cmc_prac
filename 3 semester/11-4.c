#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>


enum
{
    N = 2
};

int maxn;
int fd[N];

int work(void)
{
    fflush(stdout);
    int x;
    int pid2;
    FILE *readfd = fdopen(fd[0], "r");
    fscanf(readfd, "%d", &x);
    fscanf(readfd, "%d", &pid2);
    if (x != maxn) {
        ++x;
        int proc_num;
        if ((x - 1) % N) {
            proc_num = 1;
        } else {
            proc_num = N;
        }
        printf("%d %d\n", proc_num, x - 1);
        fflush(stdout);
        dprintf(fd[1], "%d ", x);
        dprintf(fd[1], "%d ", getpid());
        return pid2;
    } else {
        dprintf(fd[1], "%d ", x);
        dprintf(fd[1], "%d ", getpid());
        fclose(readfd);
        close(fd[0]);
        close(fd[1]);
        return 0;
    }
}

void handler(int s)
{
    int pid = work();
    if (pid) {
        kill(pid, SIGUSR1);
    } else {
        _exit(0);
    }
}

int main(int argc, char **argv)
{
    sscanf(argv[1], "%d", &maxn);
    pipe(fd);
    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler }, NULL);
    int pid[N];
    pid[0] = 1;
    pid[1] = 1;
    pid[0] = fork();
    if (!pid[0]) {
        while (1) {
            pause(); 
        }
    } else {
        pid[1] = fork();
        if (!pid[1]) {
            while (1) {
                pause();
            }
        } else {
            int z = 1;
            dprintf(fd[1], "%d %d ", z, pid[1]);
            kill(pid[0], SIGUSR1);
            int status;
            int pids = wait(&status);
            if (pids == pid[0]) {
                kill(pid[1], SIGUSR1);
            } else {
                kill(pid[0], SIGUSR1);
            }
            wait(&status);
            close(fd[0]);
            close(fd[1]);
            printf("Done\n");
            fflush(stdout);
        }
    }
}
