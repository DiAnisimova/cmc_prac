#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int median(int a, int b, int c)
  {
    if ((a <= b && a >= c) || (a >= b && a <= c))
      {
         return a;
      }
    else if ((b <= a && b >= c) || (b >= a && b <= c))
      {
        return b;
      }
    else
      {
        return c;
      }
  }

int main(void)
{
    static int a[MAX_SIZE];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      {
        scanf("%d", &a[i]);
      }
    for (int i = 2; i <= (n - 1); i += 2)
      {
        for (int j = 0; j < (n - i); j++)
          {
            a[j] = median(a[j], a[j + 1], a[j + 2]);
          }
      }
    printf("%d", a[0]);
    return 0;
}
