#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned N, K;
    scanf("%u%u", &N, &K);
    for (int i = 0; i < K; i++)
      {
        N = (N / 2) + (N % 2) * 1024 *1024 * 1024 * 2;

      }
    printf("%u", N);
    return 0;
}
