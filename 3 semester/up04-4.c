#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int
main(int argc, char **argv)
{
    enum
    {
        MIN_LONG = 0x8000000000000000
    };
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Can't open file\n");
        return 1;
    }
    long long number;
    ssize_t bytes;
    if ((bytes = read(fd, &number, sizeof(number))) == 0) {
        return 0;
    } else if (bytes != sizeof(number)) {
        return 1;
    }
    long long min = number;
    off_t minpos = 0;
    while ((read(fd, &number, sizeof(number)))  == sizeof(number)) {
        if (number < min) {
            minpos = lseek(fd, 0, SEEK_CUR) - sizeof(number);
            min = number;
        }
    }
    if (min != MIN_LONG) {
        unsigned long long umin = -(unsigned long long)min;
        if ((lseek(fd, minpos, SEEK_SET)) == -1) {
            fprintf(stderr, "error\n");
            return 1;
        }
        if (write(fd, &umin, sizeof(umin)) != sizeof(min)) {
            fprintf(stderr, "error\n");
            return 1;
        }
    }
    close(fd);
    return 0;
}

