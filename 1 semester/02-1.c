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
        for (int j = i; j > 0; j--)
          {
            printf("%d ", x[j-1]);
          }
      }
    return 0;
}
