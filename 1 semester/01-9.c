#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned N;
    scanf("%u", &N);
    int k = 0;
    while (N != 0)
      {
        if ((N % 2) == 1)
          {
            k++;
          }
        N /= 2;
      }
    printf("%d", k);
    return 0;
}
