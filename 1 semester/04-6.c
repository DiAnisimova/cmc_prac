#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000001

int main(void)
{
    int k;
    char s[MAX_LEN];
    scanf("%d", &k);
    int i = 0;
    int gaps = 0;
    getchar();
    while ((s[i] = getchar()) != '\n')
      {
        if (s[i] == ' ')
          {
            gaps++;
          }
        i++;
      }
    s[i] = '\0';
    int l = i;
    int incr = (k - l) / gaps;
    int incr1 = (k - l) % gaps;
    for (i = 0; i < l; i++)
      {
        if (s[i] != ' ')
          {
            printf("%c", s[i]);
          }
        else
          {
            for (int j = 0; j < (incr + 1); j++)
              {
                printf(" ");
              }
            if (incr1)
              {
                printf(" ");
                incr1--;
              }
          }
      }
    return 0;
}
