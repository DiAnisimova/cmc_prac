#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char **argv)
{
    enum
    {
        TABLE = 2,
        KB = 64,
        SHIFT1 = 10,
        SHIFT2 = 9
    };
    int fd;
    if ((fd = open(argv[1], O_RDONLY | O_CREAT, 0666)) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    unsigned short table;
    if ((sscanf(argv[TABLE], "%hx", &table)) != 1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    unsigned short *virt = mmap(NULL, KB << SHIFT1, PROT_READ, MAP_PRIVATE, fd, 0);
    unsigned short addr;
    while ((scanf("%hx", &addr)) != EOF) {
        virt += table / sizeof(table);
        unsigned short numpage = (addr >> SHIFT2);
        printf("num_p = %hu\n", numpage);
        unsigned short offset = addr - (numpage << SHIFT2);
        printf("offset = %hu\n", offset);
        unsigned short physnum = (virt[numpage] >> SHIFT2) << SHIFT2;
        printf("num_phys = %hu\n", physnum);
        virt -= table / sizeof(table);
        unsigned short num = *(virt + (physnum + offset) / sizeof(physnum));
        printf("%hu\n", num);
    }
    close(fd);
    return 0;
}
