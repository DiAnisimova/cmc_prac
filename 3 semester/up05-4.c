#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    const char *rights = "rwxrwxrwx";
    enum
    {
        SIZE = 9
    };
    if (str == NULL) {
        return -1;
    } else if (strlen(str) != SIZE) {
        return -1;
    }
    int r = 0;
    for (int i = 0; i < SIZE; i++) {
        if (str[i] == rights[i]) {
            r = (r << 1) + 1;
        } else {
            r <<= 1;
        }
        if (str[i] != rights[i] && str[i] != '-') {
            return -1;
        }
    }
    return r;
}
