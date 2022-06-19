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

int main(int argc, char **argv)
{
    enum 
    {
        SECOND = 2,
        PATH = 100
    };
    const char *s;
    if (!(s = getenv("XDG_RUNTIME_DIR"))) {
        if (!(s = getenv("TMPDIR"))) {
            s = "/tmp";
        }
    }
    char path[PATH_MAX + PATH] = { 0 };
    int rfd = open("/dev/urandom", O_RDONLY);
    unsigned long long val;
    read(rfd, &val, sizeof(val));
    snprintf(path, sizeof(path), "%s/ppyton%llx.py", s, val);
    int fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0700);
    close(rfd);
    FILE *f = fdopen(fd, "w");
    fprintf(f, "#!/usr/bin/python3\n");
    fprintf(f, "import os\n");
    fprintf(f, "print(");
    for (int i = 1; i < argc - 1; i++) {
        fprintf(f, "%s*", argv[i]);
    }
    fprintf(f, "%s)\n", argv[argc - 1]);
    fprintf(f, "os.remove(\"%s\")\n", path);
    fclose(f);
    execlp("/bin/sh", "sh", "-c", path, NULL);
    _exit(1);

}
