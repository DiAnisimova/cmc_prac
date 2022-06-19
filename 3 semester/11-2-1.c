#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t flag;

enum
{
    MULT = 1,
    ADD = 2
};

void handler1(int s)
{
    flag = ADD;
}

void handler2(int s)
{
    flag = MULT;
}

int main(void)
{
    flag = ADD;
    int result = 0;
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler1,
            .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGQUIT, &(struct sigaction) { .sa_handler = handler2,
            .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int number;
    while (scanf("%d", &number) != EOF) {
        if (flag == ADD) {
            __builtin_add_overflow(result, number, &result);
        } else if (flag == MULT) {
            __builtin_mul_overflow(result, number, &result);
        }
        printf("%d\n", result);
        fflush(stdout);
    }
    return 0;
}
