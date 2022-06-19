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
    setbuf(stdout, NULL);
    int n;
    scanf("%d", &n);
    int i = 0;
    for (i = 0; i < n; i++) {
        if (i != n - 1) {
            printf("%d ", i + 1);
        } else {
            printf ("%d\n", i + 1);
        }
        int pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            _exit(1);
        }
        if (pid > 0) {
            int status;
            wait(&status);
            break;
        }
    }
    return 0;
}

