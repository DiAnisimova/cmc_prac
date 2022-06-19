#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    int max1, max2, max3;
    scanf("%d%d%d", &max1, &max2, &max3);
    int t;
    if (max1 < max2)
      {
        t = max2;
        max2 = max1;
        max1 = t;
      }
    if (max2 < max3)
      {
        t = max3;
        max3 = max2;
        max2 = t;
      }
    if (max1 < max2)
      {
        t = max2;
        max2 = max1;
        max1 = t;
      }
    int a;
    for (int i = 0; i < (N - 3); i++)
      {
        scanf("%d", &a);
        if (a > max1)
          {
            max3 = max2;
            max2 = max1;
            max1 = a;
          }
        else if (a > max2)
          {
            max3 = max2;
            max2 = a;
          }
        else if (a > max3)
          {
            max3 = a;
          }
      }
    printf("%d", max1);
    printf(" ");
    printf("%d", max2);
    printf(" ");
    printf("%d", max3);
    return 0;
}
