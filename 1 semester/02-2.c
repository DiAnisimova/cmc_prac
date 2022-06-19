#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a, b;
    int x[10000];
    scanf("%d", &a);
    int i = 0;
    b = a;
    while (a != 0)
      {
        x[i] = a;
        scanf("%d", &a);
        i++;
      }
    if (b != 0)
      {
        for (int j = 0; j < i; j += 2)
          {
            printf("%d ", x[j]);
          }
        for (int j = i - 1 - (i % 2); j >= 0; j -=2)
          {
            printf("%d ", x[j]);
          }
      }
    return 0;
}
