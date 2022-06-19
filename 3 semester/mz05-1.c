#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    enum
    {
        SIZE = 1024
    };
    off_t sumsize = 0;
    for (int i = 0; i < argc; i++) {
        struct stat file;
        if (lstat(argv[i], &file) != -1 && S_ISREG(file.st_mode) 
                && file.st_size % SIZE == 0 && file.st_nlink == 1) {
            sumsize += file.st_size;
        }
    }
    printf("%lld\n", sumsize);
    return 0;
}

