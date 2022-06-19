#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    enum
    {
        ROW = 2,
        COL = 3,
        SIZE = 4
    };
    int fd = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0666);
    unsigned rows, cols;
    if ((sscanf(argv[ROW], "%u", &rows)) != 1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    if ((sscanf(argv[COL], "%u", &cols)) != 1) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    if ((ftruncate(fd, rows * cols * SIZE)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        return 1;
    }
    unsigned *virt = mmap(NULL, rows * cols * SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if (virt == MAP_FAILED) {
        return 1;
    }
    unsigned number = 1;
    int l_str = 0;
    int r_str = rows - 1;
    int l_col = 0;
    int r_col = cols - 1;
    while (number <= rows * cols) {
        for (long long i = l_col; i <= r_col; i++) {
            virt[l_str * cols + i] = number;
            number++;
        }
        if (number > rows * cols) {
            break;
        }
        l_str++;
        for (int i = l_str; i <= r_str; i++) {
            virt[r_col + i * cols] = number;
            number++;
        }
        if (number > rows * cols) {
            break;
        }
        r_col--;
        for (int i = r_col; i >= l_col; i--) {
            virt[r_str * cols + i] = number;
            number++;
        }
        if (number > rows * cols) {
            break;
        }
        r_str--;
        for (int i = r_str; i >= l_str; i--) {
            virt[l_col + i * cols] = number;
            number++;
        }
        l_col++;
    }
    munmap(virt, rows * cols * SIZE);
    close(fd);
}
