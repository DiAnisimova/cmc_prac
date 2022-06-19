#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    long long n;
    sscanf(argv[1], "%lld", &n);
    unsigned long long b0 = 0xff;
    unsigned long long b1;
    for (int i = 0; i < sizeof(n)/2; i++)
    {
      b1 = b0 << 8;
      unsigned long long x = -1 - b0 - b1;
      long long t = n & x;
      n = t + (n & b0) << 8 + (n & b1) >> 8;
      b0 <<= 16;
    }
    printf("%lld", n);
    return 0;
}
