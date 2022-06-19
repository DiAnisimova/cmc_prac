#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    enum
    {
        N = 5,
        FILE1 = 2,
        FILE2 = 3,
        FILE3 = 4,
        CMD = 1,
        RIGHTS = 0660,
        CODE = 42
    };
    int pid = fork();
    if (pid < 0) {
        return 0;
    }
    if (!pid) {
        int fd1 = open(argv[FILE1], O_RDONLY);
        int fd2 = open(argv[FILE2], O_WRONLY | O_APPEND | O_CREAT, RIGHTS);
        int fd3 = open(argv[FILE3], O_WRONLY | O_TRUNC | O_CREAT, RIGHTS);
        if (fd3 < 0) {
            _exit(CODE);
        }
        if ((dup2(fd3, STDERR_FILENO)) < 0) {
            _exit(CODE);
        }
        if (fd1 < 0 || fd2 < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(CODE);
        }
        if (dup2(fd1, STDIN_FILENO) < 0 || dup2(fd2, STDOUT_FILENO) < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(CODE);
        }
        close(fd1);
        close(fd2);
        close(fd3);
        execlp(argv[CMD], argv[CMD], NULL);
        fprintf(stderr, "%s\n", strerror(errno));
        _exit(CODE);
    } else {
        int status;
        wait(&status);
        printf("%d\n", status);
        return 0;
    }
}
