#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>


int main(int argc, char **argv)
{
    int n;
    sscanf(argv[1], "%d", &n);
    int *pid = calloc(n + 1, sizeof(*pid));
    pid[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        pid[i] = 1;
    }
    for (int i = 1; i < n + 1; i++) {
        pid[i] = fork();
        if (!pid[i]) {
            int fd = open(argv[i + 1], O_RDONLY);
            char file[PATH_MAX] = { 0 };
            int nbytes = read(fd, file, sizeof(file));
            if (nbytes < 0) {
                printf("error\n");
                _exit(1);
            }
            close(fd);
            file[strlen(file) - 1] = 0;
            execlp(file, file, (char *)NULL);
            _exit(1);
        }
    }
    int k = 0;
    for (int i = 1; i < n + 1; i++) {
        int status;
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            k++;
        }
    }
    free(pid);
    for (int i = n + 1; i < argc - 1; i++) {
        int pid1 = fork();
        if (!pid1) {
            int fd = open(argv[i + 1], O_RDONLY);
            char file[PATH_MAX];
            int nbytes = read(fd, file, sizeof(file));
            if (nbytes < 0) {
                printf("error\n");
                _exit(1);
            }
            close(fd);
            file[strlen(file) - 1] = 0;
            fputs(file, stdout);
            execlp(file, file, NULL);
            _exit(1);
        }
        int status;
        waitpid(pid1, &status, 0);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            k++;
        }
    }
    printf("%d\n", k);
    return 0;
}

