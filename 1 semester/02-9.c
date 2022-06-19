#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned n, m;
    scanf("%u", &n);
    int a[n];
    for (int i = 0; i < n; i++)
      {
        scanf("%d", &a[i]);
      }
    scanf("%u", &m);
    int x[m];
    for (int i = 0; i < m; i++)
      {
        scanf("%d", &x[i]);
      }
    for (int i = (m - 1); i >= 0; i--)
      {
        int s = a[0];
        int d = 1;
        for (int j = 1; j < n; j++)
          {
            d *= x[i];
            s += (d * a[j]);
          }
        printf("%d ", s);
      }
    return 0;
}
