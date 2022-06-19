#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

volatile sig_atomic_t lastprime;

enum
{
    MAX_COUNT = 3
};

void 
handler1(int s)
{
    static int count = 0;
    printf("%d\n", lastprime);
    fflush(stdout);
    count++;
    if (count == MAX_COUNT) {
        _exit(0);
    }
}

void
handler2(int s)
{
    _exit(0);
}

int 
isprime(int x)
{
    int i = 2;
    int find = 0;
    while (i * i <= x) {
        if (x % i == 0){
            find = 1;
        }
        i++;
    }
    if (find) {
        return 0;
    }
    return x;
}

int main(void)
{
    enum
    {
        STEP = 2
    };
    lastprime = 0;
    printf("%d\n", getpid());
    fflush(stdout);
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler1 }, NULL);
    sigaction(SIGTERM, &(struct sigaction) { .sa_handler = handler2 }, NULL);
    int low, high;
    if (scanf("%d%d", &low, &high) <= 1) {
        return 1;
    }
    int begin = low;
    if (!(low & 1)) {
        begin++;
    }
    for (int i = begin; i < high; i += STEP) {
        int res = isprime(i);
        if (res) {
            lastprime = res;
        }
    }
    printf("-1\n");
    fflush(stdout);
    _exit(0);
}
