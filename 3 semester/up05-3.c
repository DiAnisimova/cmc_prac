#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int
main(void)
{
    enum
    {
        MAXN = 32,
        ARG = 3
    };
    uint32_t n, s;
    int w;
    if ((fscanf(stdin, "%" SCNu32 "%" SCNu32 "%d", &n, &s, &w)) != ARG) {
        fprintf(stderr, "error\n");
        return 1;
    }
    uint32_t max;
    if (n == MAXN) {
        max = -1;
    } else {
        max = (1u << n) - 1;
    }
    uint32_t number = 0;
    uint32_t prev_number = 0;
    do {
        uint32_t curnum = number;
        if (number & (1u << (n - 1))) {
            curnum = -(number ^ (1u << (n - 1)));
        }
        fprintf(stdout, "|%*"PRIo32"|%*"PRIu32"|%*"PRIi32"|\n", w, number, w, number, w, curnum);
        prev_number = number;
        number += s;
    } while (number <= max && prev_number < number);
    return 0;
}
