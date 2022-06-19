#include <stdio.h>
#include <stdlib.h>

int expansion(int n)
{
    int three_m = 1;
    while (n / 3 != 0)
      {
        n /= 3;
        three_m *= 3;
      }
    return three_m;
}

int element(int n)
{
    if (n == 1)
      {
        return 0;
      }
    else
      {
        int deg_three = expansion(n);
        int rest = n - deg_three;
        if (rest > deg_three)
          {
            return element(rest - deg_three) + 2 * deg_three;
          }
        else if (rest != 0)
          {
            return element(deg_three + 1 - rest) + deg_three;
          }
        else
          {
            return element(deg_three / 3) + 2 * (deg_three / 3);
          }
      }
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int result = element(n);
    printf("%d", result);
    return 0;
}
