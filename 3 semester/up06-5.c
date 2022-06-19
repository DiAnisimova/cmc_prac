#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

enum
{
    SHIFT1 = 3 * 2,
    SHIFT2 = 3,
    MASK2 = 070,
    MASK3 = 07
};

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

static int owner(const struct stat *stb, int access) 
{
    unsigned rights = stb->st_mode >> SHIFT1;
    if (rights < access) {
        return 0;
    } else {
        return 1;
    }
}

static int isgroup(const struct stat *stb, const struct Task *task) 
{
    for (int i = 0; i < task->gid_count; i++) {
        if (task->gids[i] == stb->st_gid) {
            return 1;
        }
    }
    return 0;
}

static int group(const struct stat *stb, int access)
{
    unsigned rights = (stb->st_mode & MASK2) >> SHIFT2;
    if (rights < access) {
        return 0;
    } else {
        return 1;
    }
}

static int other(const struct stat *stb, int access)
{
    unsigned rights = stb->st_mode & MASK3;
    if (rights < access) {
        return 0;
    } else {
        return 1;
    }
}

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (task->uid == 0) {
        return 1;
    }
    if (task->uid == stb->st_uid) {
        return owner(stb, access);
    }
    if (isgroup(stb, task)) {
        return group(stb, access);
    }
    return other(stb, access);
}
