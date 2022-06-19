#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    enum
    {
        MINSIZE = 3
    };
    DIR *d = opendir(argv[1]);
    struct dirent *dd;
    int count = 0;
    while ((dd = readdir(d))) {
        char *dn = dd->d_name;
        if (strcmp(dn, ".") == 0 || strcmp(dn, "..") == 0) {
            continue;
        }
        char file[PATH_MAX];
        sprintf(file, "%s/%s", argv[1], dn);
        struct stat st;
        if (stat(file, &st) == -1) {
            fprintf(stderr, "error\n");
            continue;
        } else {
            int rights = access(file, X_OK);
            int len = strlen(file);
            int end = 0;
            if (len > MINSIZE) {
                if (file[len - 1] == 'e' && file[len - 2] == 'x' && file[len - 3] == 'e'
                        && file[len - 4] == '.') {
                    end = 1;
                }
            }
            if (S_ISREG(st.st_mode) && !rights && end) {
                count++;
            }
        }
    }
    closedir(d);
    printf("%d\n", count);
    return 0;
}
