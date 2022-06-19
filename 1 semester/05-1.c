#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    long **a = NULL;
    long **b = NULL;
    a = malloc(n * sizeof(long));
    b = malloc(n * sizeof(long));
    for (int i = 0; i < n; i++)
      {
        a[i] = malloc(n * sizeof(long));
        b[i] = malloc(n * sizeof(long));
      }
    for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
          {
            scanf("%ld%ld", &a[i][j], &b[i][j]);
            b[i][j] *= (-1);
          }
      }
    for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
          {
            printf("%ld %ld ", a[j][i], b[j][i]);
          }
        printf("\n");
      }
    for (int i = 0; i < n; i++)
      {
        free(a[i]);
        free(b[i]);
      }
    free(a);
    free(b);
    return 0;
}
