#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    enum
    {
        BUF_SIZE = 5,
        DIVISION = 100,
        BYTE = 8
    };
    int maxsum = 0;
    int is_maxsum = 0;
    int maxsum2 = 0;
    int is_maxsum2 = 0;
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd != -1) {
            int buf[BUF_SIZE] = { 0 };
            while ((read(fd, buf, sizeof(buf))) == sizeof(buf)) {
                int sum = buf[BUF_SIZE - 1];
                if (!is_maxsum) {
                    maxsum = sum;
                    is_maxsum = 1;
                } else if (!is_maxsum2 && sum < maxsum) {
                    maxsum2 = sum;
                    is_maxsum2 = 1;
                } else if (!is_maxsum2 && sum > maxsum) {
                    maxsum2 = maxsum;
                    maxsum = sum;
                    is_maxsum2 = 1;
                } else if (maxsum < sum) {
                    maxsum2 = maxsum;
                    maxsum = sum;
                } else if (maxsum2 < sum && sum != maxsum) {
                    maxsum2 = sum;
                }
            }
            close(fd);
        }
    }
    if (is_maxsum2 == 1) {
        printf("%.2lf\n", ((double)maxsum2) / DIVISION);
    }
    return 0;
}
