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

int main(void)
{
    setbuf(stdout, NULL);
    int pid = fork();
    int number;
    if (pid < 0) {
        printf("-1\n");
        return 0;
    }
    if (!pid) {
        while (scanf("%d", &number) != EOF) {
            int pid2 = fork();
            if (pid2 < 0) {
                printf("-1\n");
                _exit(1);
            }
            if (pid2 > 0) {
                int status;
                waitpid(pid2, &status, 0);
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    printf("%d\n", number);
                    fflush(stdout);
                    _exit(0);
                }
                _exit(1);
            }
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        return 0;
    }
}
