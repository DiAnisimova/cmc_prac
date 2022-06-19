#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int m;
    scanf("%d", &m);
    int k = 0;
    int r = 0;
    int i = 1;
    int m1 = m;
    while (m != 0)
      {
        if ((m % 3) == 0)
          {
            m /= 3;
          }
        if ((m % 3) == 1)
          {
            k++;
            m /=3;
          }
        if ((m % 3) == 2)
          {
            k++;
            m = m / 3 + 1;
            r = r + i;
          }
        i *= 3;
      }
    if ((m1 + r) > 1000000)
      {
        k = -1;
      }
    printf("%d", k);
    return 0;
}
