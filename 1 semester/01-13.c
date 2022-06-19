#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double x;
    unsigned short N;
    scanf("%lf", &x);
    scanf("%hu", &N);
    long double sin = x;
    long double d = x;
    unsigned short p = 1;
    for (int i = 1; i < N; i++)
      {
        d = ((-d) * x * x) / ((p + 1) * (p + 2));
        p += 2;
        sin += d;
      }
    printf("%.6Lf", sin);
    return 0;
}
