#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>

int
main(int argc, char **argv)
{
    enum 
    {
        BUF_SIZE = 2,
        HALF = 8
    };
    int is_min = 0;
    uint16_t min;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "error\n");
        return 1;
    }
    uint8_t number[BUF_SIZE];
    while ((read(fd, &number, sizeof(number))) == sizeof(number)) {
        uint16_t curnum = ((uint16_t)number[0] << HALF) + (uint16_t)number[1];
        if (!is_min && !(curnum & 1)) {
            is_min = 1;
            min = curnum;
        } else if (is_min && !(curnum & 1) && curnum < min) {
            min = curnum;
        }
    }
    if (is_min) {
        fprintf(stdout, "%"PRIu16"\n", min);
    }	
    return 0;
}

