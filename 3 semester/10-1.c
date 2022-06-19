#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <sys/wait.h>

int main(void)
{
    enum
    {
        N = 4
    };
    int fd[2];
    pipe(fd);
    struct tm *res;
    int pid[N];
    pid[0] = 0;
    for (int i = 1; i < N; i++) {
        pid[i] = 1;
    }
    pid[1] = fork();
    if (pid[1] < 0) {
        _exit(0);
    }
    for (int i = 1; i < N - 1; i++) {
        if (!pid[i]) {
            pid[i - 1] = 1;
            pid[i + 1] = fork();
            if (pid[i] < 0) {
                _exit(1);
            }
        }
    }
    if (!pid[N - 1]) {
        time_t ctime = time(NULL);
        close(fd[0]);
        for (int i = 0; i < N; i++) {
            write(fd[1], &ctime, sizeof(ctime));
        }
        close(fd[1]);
        _exit(0);
    }
    for (int i = 0; i < N - 1; i++) {
        if (!pid[i]) {
            int status;
            waitpid(pid[i + 1], &status, 0);
            if (!WIFEXITED(status)) {
                _exit(1);
            }
            close(fd[1]);
            time_t ctime;
            read(fd[0], &ctime, sizeof(ctime));
            res = localtime(&ctime);
            close(fd[0]);
            if (i == N - 2) {
            printf("D:%02d\n", res->tm_mday);
            } else if (i == 1) {
                printf("M:%02d\n", res->tm_mon + 1);
            } else if (i == 0) {
                printf("Y:%04d\n", res->tm_year + 1900);
            }
            fflush(stdout);
            _exit(0);
        }
    }
}
