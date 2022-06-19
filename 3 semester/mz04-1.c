#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    enum
    {
        MASK = 0xf00000,
        N = 4,
        SHIFT = 4,
        SIZE = 6
    };
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0600);
    unsigned number;
    char bytes[N];
    while (scanf("%u", &number) > 0) {
        for (int i = 0; i < N; i++) {
            unsigned new_mask = ((MASK + (i & 1) * (MASK >> SHIFT)) >> ((i + i / 2) * SHIFT));
            bytes[i] = (number & new_mask) >> ((SIZE - i - 1 - i / 2 - (i & 1)) * SHIFT);
        }
        int res = write(fd, bytes, sizeof(bytes));
        if (res != N) {
            return 1;
        }
    }
    close(fd);
    return 0;
}

