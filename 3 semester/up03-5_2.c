#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    enum
    {
        FIRST_ELEMENTS = 5,
        EMPTY_FILE = 1,
        DIGITS = 10,
        BUF_SIZE = 16
    };
    int state_of_file = 0;
    size_t elements = FIRST_ELEMENTS;
    char *file = calloc(elements, 1);
    size_t size = elements * 1;
    ssize_t new_size;
    if ((new_size =  getline(&file, &size, stdin)) == -1) {
        state_of_file = EMPTY_FILE;
    } else {
        if (file[new_size - 1] == '\n') {
            file[new_size - 1] = 0;
        }
        if (file[new_size - 2] == '\r') {
            file[new_size - 2] = 0;
        }
    }
    int fd;
    if (!state_of_file) {
        fd = open(file, O_RDONLY, 0);
        if (fd == -1) {
            state_of_file = EMPTY_FILE;
        }
    }
    unsigned long long digits[DIGITS];
    for (int i = 0; i < DIGITS; i++) {
        digits[i] = 0;
    }
    unsigned char buf[BUF_SIZE];
    if (!state_of_file) {
        int bytes;
        while ((bytes = read(fd, buf, BUF_SIZE))) {
            for (int i = 0; i < bytes; i++) {
                if (buf[i] >= '0' && buf[i] <= '9') {
                    digits[buf[i] - '0']++;
                }
            }
        }
        close(fd);
    }
    free(file);
    for (int i = 0; i < DIGITS; i++) {
        printf("%d %lld\n", i, digits[i]);
    }
    return 0;
}