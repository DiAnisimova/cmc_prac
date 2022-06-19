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

int 
mysys(const char *str)
{
    enum
    {
        CODE = 128,
        BADBIN = 127
    };
    int pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(BADBIN);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            return WTERMSIG(status) + CODE;
        } 
        return WEXITSTATUS(status);
    }
}
