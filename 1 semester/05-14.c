#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    unsigned max_number = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      {
        max_number *= 10;
      }
    unsigned min_number = max_number / 10;
    unsigned *arr = calloc(max_number, sizeof(unsigned));
    arr[0] = 1;
    unsigned p = 2;
    while (p != max_number)
      {
        if (arr[p - 1] != 0)
          {
            p++;
          }
        else
          {
            unsigned k = p;
            unsigned long long mult = k * p;
            while (mult <= max_number)
              {
                arr[mult - 1] = 1;
                k++;
                mult = k * p;
              }
            p++;
          }
      }
    for (unsigned i = min_number; i < max_number; i++)
      {
        if (arr[i - 1] == 0)
          {
            unsigned x = i;
            x /= 10;
            while (x != 0)
              {
                if (arr[x - 1] == 1)
                  {
                    arr[i - 1] = 1;
                    break;
                  }
                x /= 10;
              }
          }
      }
    for (unsigned i = min_number; i < max_number; i++)
      {
        if (arr[i - 1] == 0)
          {
            printf("%u ", i);
          }
      }
    return 0;
}
