#include <stdio.h>
#include <stdlib.h>

enum 
{
    MULT = 1103515245,
    INC = 12345,
    MOD = 0x80000000
};

typedef struct RandomGenerator
{   
    struct RandomOperations *ops;
    int number;
} RandomGenerator;

typedef struct RandomOperations
{
    void (*destroy)(RandomGenerator *);
    int (*next)(RandomGenerator *);
} RandomOperations;

void 
destroy(RandomGenerator *s)
{
    free(s);
}

struct RandomOperations op;

int 
next(RandomGenerator *s) 
{
    s->number = ((unsigned long long)s->number * MULT + INC) % MOD;
    return s->number;
}

struct RandomOperations op = { destroy, next };

RandomGenerator *
random_create(int seed)
{
    RandomGenerator *s = calloc(1, sizeof(*s));
    s->ops = &op;
    s->number = seed;
    return s;
}


