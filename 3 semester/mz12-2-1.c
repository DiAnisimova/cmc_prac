#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    enum
    {
        COUNT = 1,
        MODULO = 2,
        PROG = 3
    };
    int count, modulo;
    sscanf(argv[COUNT], "%d", &count);
    sscanf(argv[MODULO], "%d", &modulo);
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    int p1 = fork();
    if (!p1) {
        int p2 = fork();
        if (!p2) {
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0], 0);
            dup2(fd2[1], 1);
            close(fd1[0]);
            close(fd2[1]);
            fflush(stdout);
            execlp(argv[PROG], argv[PROG], NULL);
            _exit(1);
        }
        close(fd1[0]);
        close(fd2[1]);
        close(fd2[0]);
        for (int i = 1; i <= count; i++) {
            dprintf(fd1[1], "%d ", (i * i) % modulo);
        }
        close(fd1[1]);
        wait(NULL);
    } else {
        int p3 = fork();
        if (!p3) {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[1]);
            int p4 = fork();
            if (!p4) {
                int number;
                FILE *readfd = fdopen(fd2[0], "r");
                while (fscanf(readfd, "%d", &number) > 0) {
                    printf("%d\n", number);
                }
                fclose(readfd);
                _exit(0);
            }
            close(fd2[0]);
            wait(NULL);
        } else {
            wait(NULL);
            wait(NULL);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            printf("0\n");
            _exit(0);
        }
    }
}

