#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

unsigned long long hash_function(unsigned long long);

int
main(int argc, char **argv)
{
    enum
    {
        N = 4,
        OFFSET = 2,
        ARGH0 = 2
    };
    if (argc < N) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    unsigned long long h0;
    if ((sscanf(argv[ARGH0], "%llx", &h0)) <= 0) {
        fprintf(stderr, "error\n");
        return 1;
    }
    unsigned long long count;
    if ((sscanf(argv[N - 1], "%llu", &count)) <= 0) {
        fprintf(stderr, "error\n");
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0660);
    if (fd <= 0) {
        fprintf(stderr, "error\n");
        return 1;
    }
    if (count == 0) {
        close(fd);
        return 0;
    }
    off_t end = lseek(fd, 0, SEEK_END);
    for (unsigned long long i = 0; i < count; i++) {
        if ((lseek(fd, end + (count - 1 - i) * sizeof(h0), SEEK_SET)) == -1) {
            fprintf(stderr, "error\n");
            return 1;
        }
        if ((write(fd, &h0, sizeof(h0))) != sizeof(h0)) {
            fprintf(stderr, "error\n");
            return 1;
        }
        h0 = hash_function(h0);
    }
    close(fd);
    return 0;
}

