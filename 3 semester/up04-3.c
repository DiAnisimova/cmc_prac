#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
} Node;

int
search(Node tree, int fd)
{
    if (tree.right_idx) {
        off_t currpos = lseek(fd, 0, SEEK_CUR);
        if ((lseek(fd, tree.right_idx * sizeof(tree), SEEK_SET)) < 0) {
            fprintf(stderr, "error\n");
            return 1;
        }
        Node tree_r;
        if ((read(fd, &tree_r, sizeof(tree_r))) != sizeof(tree_r)) {
            fprintf(stderr, "Reading error\n");
            return 1;
        }
        int flag = search(tree_r, fd);
        if (flag) {
            return 1;
        }
        lseek(fd, currpos, SEEK_SET);
    }
    printf("%d\n", tree.key);
    if (tree.left_idx) {
        off_t currpos = lseek(fd, 0, SEEK_CUR);
        if ((lseek(fd, tree.left_idx * sizeof(tree), SEEK_SET)) < 0) {
            fprintf(stderr, "error\n");
            return 1;
        }
        Node tree_l;
        if ((read(fd, &tree_l, sizeof(tree_l))) != sizeof(tree_l)) {
            fprintf(stderr, "Reading error\n");
            return 1;
        }
        int flag = search(tree_l, fd);
        if (flag) {
            return 1;
        }
        lseek(fd, currpos, SEEK_SET);
    }
    return 0;
}

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Can't open file\n");
        return 1;
    }
    Node tree;
    if ((read(fd, &tree, sizeof(tree))) != sizeof(tree)) {
        fprintf(stderr, "Reading error\n");
        return 1;
    }
    int flag = search(tree, fd);
    close(fd);
    if (flag) {
        return 1;
    }
    return 0;
}
