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
    enum
    {
        FATHER = 1,
        SON = 2,
        GRANDSON = 3
    };
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed: %s\n", strerror(errno));
        _exit(1);
    }
    if (pid > 0) {
        int status;
        if ((wait(&status)) < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(1);
        }
        printf("%d\n", FATHER);
        return 0;
    } else {
       int pid2 = fork();
       if (pid2 < 0) {
           fprintf(stderr, "fork failed: %s\n", strerror(errno));
           _exit(1);
       }
       if (pid2 > 0) {
           int status2;
           if ((wait(&status2)) < 0) {
               fprintf(stderr, "%s\n", strerror(errno));
               _exit(1);
           }
           printf("%d ", SON);
       } else {
           printf("%d ", GRANDSON);
       }
    }
}
