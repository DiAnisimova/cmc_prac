#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

int main(void)
{
    char s[MAX_SIZE];
    scanf("%255s", s);
    int even = 0;
    int odd = 0;
    int t_even = 0;
    int t_odd = 0;
    int l = strlen(s);
    for (int i = 0; i < l; i++)
      {
        if (s[i] == 'A' && i % 2 == 0)
          {
            odd++;
          }
        else if (s[i] == 'A')
          {
            even++;
          }
      }
    for (int i = 0; i < l; i++)
      {
        if (s[i] == 'A' && i % 2 == 0)
          {
            if (t_odd + (even - t_even) == t_even + (odd - t_odd - 1))
              {
                printf("%d ", i + 1);
              }
            t_odd++;
          }
        else if (s[i] == 'A')
          {
            if (t_odd + (even - t_even - 1) == t_even + (odd - t_odd))
              {
                printf("%d ", i + 1);
              }
            t_even++;
          }
        else
          {
            if (t_odd + (even - t_even) == t_even + (odd - t_odd))
              {
                printf("%d ", i + 1);
              }
          }
      }
    return 0;
}
