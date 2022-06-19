#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000002

void z_func (char *s, int *z, int len)
{
	int left = 0;
	int right = 0;
	for (int i = 1; i < len; i++)
      {
		if (i <= right)
          {
            if ( right - i + 1 < z[i - left])
              {
                z[i] = right - i + 1;
              }
            else
              {
                z[i] = z[i - left];
              }
          }
		while (i + z[i] < len && s[z[i]] == s[i + z[i]])
          {
            z[i]++;
          }
		if (i + z[i] - 1 > right)
          {
            left = i;
            right = i + z[i] - 1;
          }
	  }
}

int main(void)
{
    char s[MAX_LEN];
    fgets(s, MAX_LEN, stdin);
    static int z[MAX_LEN];
    for (int i = 0; i < MAX_LEN; i++)
      {
        z[i] = 0;
      }
    int len = strlen(s) - 1;
    z_func(s, z, len);
    for (int i = 1; i < len; i++)
      {
        if (z[i] + i == len)
          {
            printf("%d ", i);
          }
      }
    printf("%d", len);
    return 0;
}
