#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    enum
    {
        OUT = 1,
        MOD = 2,
        PATH = 100
    };
    int mod;
    sscanf(argv[MOD], "%d", &mod);
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
    close(rfd);
    snprintf(path, sizeof(path), "%s/%s%llx.c", s, argv[OUT], val);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    FILE *f = fdopen(fd, "w");
    fprintf(f, "#include <stdio.h>\n");
    fprintf(f, "\n");
    fprintf(f, "int main(void)\n");
    fprintf(f, "{\n");
    fprintf(f, "    int number;\n");
    fprintf(f, "    scanf(\"%%d\", &number);\n");
    fprintf(f, "    unsigned long long sum = number;\n");
    fprintf(f, "    sum = (sum * (sum + 1)) / 2;\n");
    fprintf(f, "    printf(\"%%llu\\n\", sum %% %d);\n", mod);
    fprintf(f, "    return 0;\n");
    fprintf(f, "}");
    fclose(f);
    int pid = fork();
    if (pid < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        _exit(1);
    }
    if (!pid) {
        execlp("gcc", "gcc", path, "-o", argv[OUT], NULL);
        _exit(1);
    }
    wait(NULL);
    chmod(argv[OUT], 0751);
    _exit(0);
}

