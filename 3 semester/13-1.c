#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/mman.h>

void 
work(int sem, unsigned long long *number, int i, int maxval, int nproc)
{
    while (1) {
        struct sembuf sop[1];
        struct sembuf oper;
        oper.sem_num = i;
        oper.sem_op = -1;
        oper.sem_flg = 0;
        sop[0] = oper;
        int flag = semop(sem, sop, 1);
        if (flag < 0) {
            exit(0);
        }
        printf("%d %llu %llu\n", i + 1, number[0], number[1]);
        fflush(stdout);
        number[0]++;
        if (number[0] > maxval) {
            semctl(sem, 0, IPC_RMID);
            exit(0);
        }
        number[1] = i + 1;
        oper.sem_num = ((number[0] % nproc) * (number[0] % nproc) * (number[0] % nproc) * (number[0] % nproc)) % nproc;
        oper.sem_op = 1;
        sop[0] = oper;
        flag = semop(sem, sop, 1);
        if (flag < 0) {
            fprintf(stderr, "semop: %s\n", strerror(errno));
            exit(0);
        }
    }
}

int main(int argc, char **argv)
{
    enum
    {
        NPROC = 1,
        KEY = 2,
        MAXVAL = 3
    };
    int nproc, maxval;
    key_t key;
    sscanf(argv[NPROC], "%d", &nproc);
    sscanf(argv[KEY], "%d", &key);
    sscanf(argv[MAXVAL], "%d", &maxval);
    int sem = semget(key, nproc, 0600 | IPC_CREAT | IPC_EXCL);
    unsigned short *tmp = calloc(nproc, sizeof(*tmp));
    semctl(sem, 0, SETALL, tmp);
    free(tmp);
    semctl(sem, 0, SETVAL, 1);
    unsigned long long *number = mmap(NULL, 2 * sizeof(*number), PROT_WRITE | PROT_READ,  
            MAP_SHARED | MAP_ANON, 0, 0);
    number[0] = 0;
    number[1] = 0;
    for (int i = 0; i < nproc; i++) {
        int pid = fork();
        if (!pid) {
            work(sem, number, i, maxval, nproc);
            _exit(0);
        }
    }
    for (int i = 0; i < nproc; i++) {
        int status;
        wait(&status);
    }
    _exit(0);
}

