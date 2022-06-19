#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t count;
volatile sig_atomic_t flag = 0;

enum
{
    NUM1 = 5,
    NUM2 = 4
};

void handler1(int s)
{
    flag = SIGUSR1;
    count += NUM1;
}

void handler2(int s)
{
    flag = SIGUSR2;
    count -= NUM2;
}

int main(void)
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigaddset(&s1, SIGUSR2);
    sigprocmask(SIG_BLOCK, &s1, &s2);
    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler1,
            .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGUSR2, &(struct sigaction) { .sa_handler = handler2,
            .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        while (!flag) {
            sigsuspend(&s2);
        }
        printf("%d %d\n", flag, count);
        fflush(stdout);
        if (count < 0) {
            _exit(0);
        }
        flag = 0;
    }
    return 0;
}

