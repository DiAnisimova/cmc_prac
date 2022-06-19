#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

enum
{
    MAXN = 5
};

void 
handler(int s)
{
    static int count = 0;
    if (count == MAXN) {
        _exit(0);
    }
    printf("%d\n", count++);
    fflush(stdout);
}

int main(void)
{
    sigaction(SIGHUP, &(struct sigaction) { .sa_handler = handler }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
}
