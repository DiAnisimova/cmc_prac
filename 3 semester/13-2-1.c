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

int main(int argc, char **argv)
{
    enum
    {
        COUNT = 1,
        KEY = 2,
        NPROC = 3,
        ITER = 4,
        BEGIN = 5,
        BASE = 10
    };
    int count, nproc, iter_count;
    key_t key;
    sscanf(argv[COUNT], "%d", &count); 
    sscanf(argv[KEY], "%d", &key);
    sscanf(argv[NPROC], "%d", &nproc);
    sscanf(argv[ITER], "%d", &iter_count);
    int sem = semget(key, count, 0600 | IPC_CREAT | IPC_EXCL);
    unsigned short *tmp = calloc(count, sizeof(*tmp));
    for (int i = 0; i < count; i++) {
        tmp[i] = 1;
    }
    semctl(sem, 0, SETALL, tmp);
    free(tmp);
    int *buf;
    int shmid = shmget(key, count * sizeof(*buf), 0600 | IPC_CREAT);
    buf = shmat(shmid, 0, 0);
    for (int i = 0; i < count; i++) {
        scanf("%d", &buf[i]);
    }
    for (int i = 0; i < nproc; i++) {
        int pid = fork();
        if (!pid) {
            int begin;
            sscanf(argv[BEGIN + i],"%d", &begin);
            srand(begin);
            for (int j = 0; j < iter_count; j++) {
                int ind1 = abs(rand()) % count;
                int ind2 = abs(rand()) % count;
                int value = abs(rand() % BASE);
                int low = ind1;
                int high = ind2;
                if (low > high) {
                    low = ind2;
                    high = ind1;
                }
                struct sembuf sop[2];
                struct sembuf oper;
                oper.sem_num = low;
                oper.sem_op = -1;
                oper.sem_flg = 0;
                sop[0] = oper;
                //int flag = semop(sem, sop, 1);
                oper.sem_num = high;
                sop[0] = oper;
                int flag = semop(sem, sop, 2);
                if (flag < 0) {
                    exit(1);
                }
                operation(buf, ind1, ind2, value);
                oper.sem_op = 1;
                sop[0] = oper;
                //flag = semop(sem, sop, 1);
                oper.sem_num = low;
                sop[0] = oper;
                flag = semop(sem, sop, 1);
                if (flag < 0) {
                    exit(1);
                }
            }
            exit(0);
        }
    }
    for (int i = 0; i < nproc; i++) {
        wait(NULL);
    }
    for (int i = 0; i < count; i++) {
        printf("%d\n", buf[i]);
    }
    shmdt(buf);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(sem, 0, IPC_RMID);
    return 0;
}
