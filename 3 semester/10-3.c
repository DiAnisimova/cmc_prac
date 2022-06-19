#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    enum
    {
        CMD1 = 1,
        FILE1 = 4,
        CMD2 = 2,
        CMD3 = 3,
        FILE2 = 5
    };
    int fd[2];
    int flag = pipe(fd);
    if (flag < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    int pid2 = fork();
    if (!pid2) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        int pid1 = fork();
        if (pid1 < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(1);
        }
        if (!pid1) {
            int file1 = open(argv[FILE1], O_RDONLY);
            if (file1 < 0) {
                _exit(1);
            }
            if (dup2(file1, STDIN_FILENO) < 0) {
                _exit(1);
            }
            close(file1);
            execlp(argv[CMD1], argv[CMD1], NULL);
            _exit(1);
        }
        int status;
        waitpid(pid1, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status)) {
            _exit(1);
        }
        int pid4 = fork();
        if (!pid4) {
            execlp(argv[CMD2], argv[CMD2], NULL);
            _exit(1);
        }
        waitpid(pid2, &status, 0);
        _exit(0);
    } else {
        int pid3 = fork();
        if (pid3 < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(1);
        } 
        if (!pid3) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            int file2 = open(argv[FILE2], O_WRONLY | O_APPEND | O_CREAT, 0660);
            dup2(file2, STDOUT_FILENO);
            close(file2);
            execlp(argv[CMD3], argv[CMD3], NULL);
            _exit(1);
        }
        close(fd[0]);
        close(fd[1]);
        int status;
        waitpid(pid2, &status, 0);
        waitpid(pid3, &status, 0);
        _exit(0);
    }
}
