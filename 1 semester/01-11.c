#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned N;
    scanf("%u", &N);
    unsigned p = 1;
    for (int i = 0; i < 24; i++)
      {
        p = p * 2;
      }
    unsigned b = N / p;
    N = N % p;
    b = 255 - b;
    N = N + p * b;
    printf("%u", N);
    return 0;
}
