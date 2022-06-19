#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

int work(int rfd, int wfd, int maxnum, int proc)
{
    int x;
    FILE *readfd = fdopen(rfd, "r");
    while (fscanf(readfd, "%d", &x) == 1 && x != maxnum) {
        ++x;
        printf("%d %d\n", proc, x - 1); 
        fflush(stdout);
        if (x == maxnum) {
            break;
        }
        dprintf(wfd, "%d ", x);
    }
    fclose(readfd);
    return 0;
}

int main(int argc, char **argv)
{
    int maxnum;
    if ((sscanf(argv[1], "%d", &maxnum)) != 1) {
        return 1;
    }
    int p12[2];
    int p21[2];
    int flag = pipe(p12);
    if (flag < 0) {
        return 1;
    }
    flag = pipe(p21);
    if (flag < 0) {
        return 1;
    }
    if (!fork()) {
        close(p21[1]); 
        close(p12[0]);
        flag = work(p21[0], p12[1], maxnum, 1);
        close(p12[1]);
        if (flag < 0) {
            _exit(1);
        }
        _exit(0);
    }
    if (!fork()) {
        close(p12[1]); 
        close(p21[0]);
        flag = work(p12[0], p21[1], maxnum, 2);
        close(p21[1]);
        if (flag) {
            _exit(1);
        }
        _exit(0);
    } 
    int z = 1;
    dprintf(p21[1], "%d ", z);
    fflush(stdout);
    close(p12[0]); 
    close(p12[1]);
    close(p21[0]); 
    close(p21[1]);
    wait(NULL);
    wait(NULL);
    fprintf(stdout, "Done\n");
    return 0;
}
