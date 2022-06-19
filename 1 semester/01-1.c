#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    int a;
    scanf("%d", &a);
    int max = a;
    int min = a;
    for (int i = 0; i < (N - 1); i++)
      {
        scanf("%d", &a);
        if (a < min)
          {
            min = a;
          }
        if (a > max)
          {
            max = a;
          }
      }
    printf("%d", max - min);
    return 0;
}
