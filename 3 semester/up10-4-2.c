#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void
end(int begin, int k, int *pids)
{
    for (int i = begin; i < k; i++) {
        kill(pids[i], SIGKILL);
    }
    int status;
    while (wait(&status) != -1) {
    }
    free(pids);
    _exit(1);
}

void
closeall(int *fd1, int *fd2, int k, int *pids)
{
    int flag1 = close(fd1[0]);
    int flag2 = close(fd1[1]);
    int flag3 = 0, flag4 = 0;
    if (fd2) {
        flag3 = close(fd2[0]);
        flag4 = close(fd2[1]);
    }
    if (flag1 || flag2 || flag3 || flag4) {
        if (!pids) {
            _exit(1);
        }
        end(0, k, pids);
    }
}

int main(int argc, char **argv)
{
    enum
    {
        N = 2
    };
    if (argc == 1) {
        _exit(0);
    }
    int *pids = calloc(argc, sizeof(*pids));
    int fd1[N];
    int fd2[N];
    if (pipe(fd1) < 0) {
        free(pids);
        _exit(1);
    }
    int n_proc = 0;
    for (int i = 0; i < argc - 1; i++) {
        if (pipe(fd2) < 0) {
            closeall(fd1, NULL, i, pids);
            end(0, i, pids);
        }
        pids[i] = fork(); 
        if (pids[i] < 0) {
            closeall(fd1, fd2, i, pids);
            end(0, i, pids);
        }
        if (!pids[i]) {
            if (i + 1 != argc - 1) {
                if (dup2(fd2[1], 1) < 0) {
                    closeall(fd1, fd2, i + 1, NULL);
                    _exit(1);
                }
            }
            if (i != 0) {
                if (dup2(fd1[0], 0) == -1) {
                    closeall(fd1, fd2, i + 1, NULL);
                    _exit(1);
                }
            }
            closeall(fd1, fd2, i + 1, NULL);
            execlp("/bin/sh", "sh", "-c",  argv[i + 1], NULL);
            _exit(1);
        }
        n_proc++;
        closeall(fd1, NULL, i + 1, NULL);
        fd1[0] = fd2[0];
        fd1[1] = fd2[1];
    }
    closeall(fd1, NULL, n_proc, pids);
    for (int i = 0; i < argc - 1; i++) {
        int status;
        if (wait(&status) < 0) {
            end(i, argc - 1, pids);
        }
    }
    if (pids) {
        free(pids);
        _exit(0);
    }
}
