#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    unsigned short k;
    scanf("%d%hu", &N, &k);
    int d = 1;
    for (int i = 0; i < k; i++)
      {
        d *= 2;
      }
    printf("%d", N % d);
    return 0;
}
