#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    int a;
    scanf("%d", &a);
    int max = a;
    int k = 1;
    for (int i = 0; i < (N - 1); i++)
      {
        scanf("%d", &a);
        if (a == max)
          {
            k++;
          }
        if (a > max)
          {
            max = a;
            k = 1;
          }
      }
    printf("%d", k);
    return 0;
}
