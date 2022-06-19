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
func(char *prog)
{
    int pid = fork();
    if (pid < 0) {
        return 0;
    }
    if (!pid) {
        execlp(prog, prog, NULL);
        _exit(1);
    } else {
        int status;
        wait(&status);
        return WIFEXITED(status) && (WEXITSTATUS(status) == 0);
    }
}

int main(int argc, char **argv)
{
    enum
    {
        CMD1 = 1,
        CMD2 = 2,
        CMD3 = 3
    };
    return !((func(argv[CMD1]) || (func(argv[CMD2]))) && func(argv[CMD3]));
}

