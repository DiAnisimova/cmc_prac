#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct MyBuf
{
    long mtype;
    int64_t val;
};

void
end(int *pids, int msgid, int n)
{
    for (int i = 0; i < n; i++) {
        if (pids[i]) {
            kill(pids[i], SIGKILL);
        }
    }
    int status;
    while (wait(&status) != -1) {
    }
    free(pids);
    _exit(1);
}

int main(int argc, char **argv)
{
    enum
    {
        KEY = 1,
        N = 2,
        VALUE1 = 3,
        VALUE2 = 4,
        MAXVAL = 5
    };
    key_t key;
    int n;
    int64_t value1, value2, maxval; 
    sscanf(argv[KEY], "%d", &key);
    sscanf(argv[N], "%d", &n);
    sscanf(argv[VALUE1], "%" SCNi64, &value1);
    sscanf(argv[VALUE2], "%" SCNi64, &value2);
    sscanf(argv[MAXVAL], "%" SCNi64, &maxval);
    int *pids = calloc(n, sizeof(*pids));
    int msgid = msgget(key, 0600 | IPC_CREAT | IPC_EXCL);
    if (msgid < 0) {
        fprintf(stderr, "error: %s\n", strerror(errno));
        _exit(1);
    }
    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            msgctl(msgid, IPC_RMID, NULL);
            end(pids, msgid, n);
        }
        if (!pids[i]) {
            free(pids);
            while (1) {
                struct MyBuf rv;
                int r = msgrcv(msgid, &rv, sizeof(rv) - sizeof(rv.mtype), i + 1, 0);
                if (r < 0) {
                    _exit(0);
                }
                int64_t x1, x2, x3;
                x1 = rv.val;
                r = msgrcv(msgid, &rv, sizeof(rv) - sizeof(rv.mtype), i + 1, 0);
                if (r < 0) {
                    _exit(0);
                }
                x2 = rv.val;
                x3 = x1 + x2;
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                if (abs(x3) > maxval) {
                    msgctl(msgid, IPC_RMID, NULL);
                    _exit(0);
                }
                rv.val = x2;
                rv.mtype = x3 % n + 1;
                msgsnd(msgid, &rv, sizeof(rv) - sizeof(rv.mtype), 0);
                rv.val = x3;
                msgsnd(msgid, &rv, sizeof(rv) - sizeof(rv.mtype),     0);
            }
            _exit(0);
        }
    }
    struct MyBuf tmp;
    tmp.mtype = 1,
    tmp.val = value1;
    msgsnd(msgid, &tmp, sizeof(tmp) - sizeof(tmp.mtype), 0);
    tmp.val = value2;
    msgsnd(msgid, &tmp, sizeof(tmp) - sizeof(tmp.mtype), 0);
    for (int i = 0; i < n; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }
    free(pids);
    msgctl(msgid, IPC_RMID, NULL);
    _exit(0);
}

