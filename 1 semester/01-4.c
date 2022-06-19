#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    int a;
    scanf("%d", &a);
    int k = 1;
    int k1 = 1;
    int b;
    for (int i = 0; i < (N - 1); i++)
      {
        scanf("%d", &b);
        if (b > a)
          {
            k1++;
          }
        else
          {
            if (k1 > k)
              {
                k = k1;
              }
            k1 = 1;
          }
        a = b;
      }
    if (k1 > k)
      {
        k = k1;
      }
    printf("%d", k);
    return 0;
}
