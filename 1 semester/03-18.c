#include <stdio.h>
#include <stdlib.h>

#define MAX_REPEAT 2010

int add(int x)
{
  int y = 1;
  while (y <= x)
    {
      y *= 10;
    }
  y = y * x + x;
  return y;
}

int main(void)
{
    int n, a, x;
    scanf("%d%d", &n, &a);
    x = n % MAX_REPEAT;
    int is_found = 0;
    for (int i = 0; i < MAX_REPEAT; i++)
      {
        if (a == x)
          {
            is_found = 1;
            break;
          }
        else
          {
            x = add(x) % MAX_REPEAT;
          }
      }
    if (is_found)
      {
        printf("YES");
      }
    else
      {
        printf("NO");
      }
    return 0;
}
