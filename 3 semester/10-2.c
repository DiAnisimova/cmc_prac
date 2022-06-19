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
    int number;
    int fd[2];
    int flag = pipe(fd);
    if (flag < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 0;
    }
    int pidg = -1;
    int pids = fork();
    if (pids < 0) {
        close(fd[1]);
        close(fd[0]);
        fprintf(stderr, "%s\n", strerror(errno));
        _exit(1);
    }
    if (!pids) {
        pidg = fork();
        if (pidg < 0) {
            close(fd[1]);
            close(fd[0]);
            fprintf(stderr, "%s\n",strerror(errno));
            _exit(1);
        }
        if (!pidg) {
            long long sum = 0;
            int n;
            int n_bytes;
            while ((n_bytes = read(fd[0], &n, sizeof(n)) > 0)) {
                sum += n;
            }
            if (n_bytes < 0) {
                _exit(1);
            }
            printf("%lld\n", sum);
            close(fd[0]);
            close(fd[1]);
            _exit(0);
        }
        int status;
        wait(&status);
        close(fd[0]);
        close(fd[1]);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            _exit(0);
        }
        _exit(1);
    } else {
        while(scanf("%d", &number) != EOF) {
            int k = write(fd[1], &number, sizeof(number));
            if (k < 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                break;
            }
        }
        close(fd[0]);
        close(fd[1]);
        int status;
        wait(&status);
        return 0;
    }
}
