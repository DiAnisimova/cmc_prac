#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x, y, t;
    scanf("%d%d", &x, &y);
    if (x < 0)
      {
        x = -x;
      }
    if (y < 0)
      {
        y = -y;
      }
    if (x > y)
      {
        t = x;
        x = y;
        y = t;
      }
    printf("%d", y + x + y - x - ((y - x) % 2));
    return 0;
}
