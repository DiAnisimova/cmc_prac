#include <stdio.h>
#include <stdlib.h>

unsigned long **mult(unsigned long **a, unsigned long **b, unsigned long k, unsigned long p, unsigned long **res)
{
    for (int i = 0; i < k; i++)
      {
        for (int j = 0; j < k; j++)
          {
            res[i][j] = 0;
          }
      }
    for (unsigned long i = 0; i < k; i++)
      {
        for (int j = 0; j < k; j++)
          {
            for (int l = 0; l < k; l++)
              {
                res[i][j] += (a[i][l] * b[l][j]) % p;
                res[i][j] %= p;
              }
          }
      }
    for (int i = 0; i < k; i++)
      {
        for (int j = 0; j < k; j++)
          {
            printf("%ld ", res[i][j]);
          }
        printf("\n");
      }
    for (int i = 0; i < k; i++)
      {
        for (int j = 0; j < k; j++)
          {
            res[i][j] = res[i][j] % p;
          }
      }
    return res;
}

int main(void)
{
    unsigned long k, n, p;
    scanf("%ld%ld%ld", &k, &n, &p);
    n -= k;
    unsigned long *f = malloc(k * sizeof(unsigned long));
    for (int i = 0; i < k; i++)
      {
        scanf("%ld", &f[k - 1 - i]);
        f[k - 1 - i] %= p;
      }
    unsigned long **a;
    unsigned long **b;
    unsigned long **res;
    res = malloc(k * sizeof(unsigned long *));
    for (int i = 0; i < k; i++)
      {
        res[i] = calloc(k, sizeof(unsigned long));
      }
    a = malloc(k * sizeof(unsigned long *));
    for (unsigned long i = 0; i < k; i++)
      {
        a[i] = calloc(k, sizeof(unsigned long));
      }
    for (int i = 0; i < k; i++)
      {
        scanf("%ld", &a[0][i]);
        a[0][i] %= p;
      }
    for (int i = 1; i < k; i++)
      {
        a[i][i - 1] = 1;
      }
    for (int i = 0; i < k; i++)
      {
        for (int j = 0; j < k; j++)
          {
            printf("%d ", a[i][j]);
          }
        printf("\n");
      }
    b = malloc(k * sizeof(unsigned long *));
    for (unsigned long i = 0; i < k; i++)
      {
        b[i] = calloc(k, sizeof(unsigned long));
      }
    for (int i = 0; i < k; i++)
      {
        scanf("%ld", &b[0][i]);
        b[0][i] %= p;
      }
    for (int i = 1; i < k; i++)
      {
        b[i][i - 1] = 1;
      }
    for (int i = 0; i < n; i++)
      {
        a = mult(a, b, k, p, res);
      }
    unsigned long fn = 0;
    for (int i = 0; i < k; i++)
      {
        fn += a[0][i] * f[i];
      }
    fn %= p;
    printf("%ld", fn);
    for (int i = 0; i < k; i++)
      {
        free(a[i]);
      }
    free(a);
    free(f);
    return 0;
 }
