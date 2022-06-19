#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a, b, c;
    scanf("%d%d", &a, &b);
    int s = a;
    while (b != 0)
      {
        scanf("%d", &c);
        if (c != 0)
          {
            s = s + b * c;
            scanf("%d", &b);
          }
        else
          {
            s += b;
            b = 0;
          }
      }
    printf("%d", s);
    return 0;
}
