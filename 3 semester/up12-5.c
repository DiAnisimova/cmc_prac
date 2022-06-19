#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t flag;

enum
{
    BIT0 = 1,
    BIT1 = 2,
    RECEIVED = 0,
    END = 3,
    BYTE = 8
};

void 
handler0(int s) 
{
    flag = BIT0;
}

void 
handler1(int s)
{
    flag = BIT1;
}

void
handlerres(int s)
{
    flag = RECEIVED;
}

void 
handlerend(int s) {
    flag = END;
}

int main(int argc, char **argv)
{
    flag = RECEIVED;
    sigaction(SIGUSR1, &(struct sigaction) { .sa_handler = handler0 }, NULL);
    sigaction(SIGUSR2, &(struct sigaction) { .sa_handler = handler1 }, NULL);
    sigaction(SIGALRM, &(struct sigaction) { .sa_handler = handlerres }, NULL);
    sigaction(SIGIO, &(struct sigaction) { .sa_handler = handlerend }, NULL);
    int pid1 = fork();
    if (pid1 < 0) {
        _exit(1);
    }
    if (!pid1) {
        printf("pid1\n");
        int bits = 0;
        unsigned char c = 0;
        while (1) {
            //pause();
            if (flag) {
               //printf("flag 1\n");
               if (flag == BIT0) {
                   printf("bit0\n");
                   c <<= 1;
               } else if (flag == BIT1) {
                   printf("bit1\n");
                   c = (c << 1) + 1;
               } else {
                   printf("bit???\n");
                   _exit(0);
               }
               bits++;
               if (bits == BYTE) {
                   putchar(c);
                   bits = 0;
               }
               kill(0, SIGALRM); 
           }
       }
    } else {
        int pid2 = fork();
        if (pid2 < 0) {
            _exit(1);
        }
        if (!pid2) {
            printf("pid2\n");
            int fd = open(argv[1], O_RDONLY);
            unsigned char c;
            int k = sizeof(c) * BYTE;
            read(fd, &c, sizeof(c));
            while (1) {
                //pause();
                if (!flag) {
                    //printf("not flag 2\n");
                    if (k == 0) {
                        if (read(fd, &c, sizeof(c)) <= 0) {
                            kill(pid1, SIGIO);
                            close(fd);
                            _exit(0);
                        }
                        k = sizeof(c) * BYTE;
                    }
                    if (c & 1) {
                        printf("send 1\n");
                        kill(pid1, SIGUSR2);
                    } else {
                        printf("send 2\n");
                        kill(pid1, SIGUSR1);
                    }
                    k--;
                    c >>= 1;
                }
                //pause();
            }
        }
        wait(NULL);
        wait(NULL);
        _exit(0);
    }
}
            

