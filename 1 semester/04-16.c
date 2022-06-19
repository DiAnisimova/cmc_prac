#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 2000

void shift(int *pos_t , int k0, int len, int i)
{
    int t = pos_t[i];
    for (int j = 0; j < k0; j++)
      {
        pos_t[j] = (len + pos_t[j] - t) % len;
      }
}

int compare(int *pos_t, int *pos, int k0, int nul_pos, int nul_pos_t)
{
    for (int i = 0; i < k0; i++)
      {
        if (pos_t[(i + nul_pos_t) % k0] < pos[(i + nul_pos) % k0])
          {
            return 1;
          }
        else if (pos_t[(i + nul_pos_t) % k0] > pos[(i + nul_pos) % k0])
          {
            return 0;
          }
      }
    return 0;
}

int main(void)
{
    int pos[MAX_SIZE];
    int pos_t[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
      {
        pos[i] = -1;
      }
    int k0 = 0;
    int len = 0;
    char c;
    while ((c = getchar()) == '0' || c == '1')
      {
        if (c == '0')
          {
            pos[k0] = len;
            pos_t[k0] = len;
            k0++;
          }
        len++;
      }
    if (k0 == 0)
      {
        for (int i = 0; i < len; i++)
          {
            printf("1");
          }
      }
    else
      {
        int nul_pos = 0;
        int nul_pos_t = 0;
        if (pos_t[0] != 0)
          {
            shift(pos_t, k0, len, 0);
            shift(pos, k0, len, 0);
          }
        for (int i = 1; i < k0; i++)
          {
            shift(pos_t, k0, len, i);
            nul_pos_t++;
            if (compare(pos_t, pos, k0, nul_pos, nul_pos_t))
              {
                for (int i = 0; i < k0; i++)
                  {
                    pos[i] = pos_t[i];
                  }
                nul_pos = nul_pos_t;
              }
          }
        int position0 = nul_pos;
        for (int i = 0; i < len; i++)
          {
            if (i == pos[position0])
              {
                printf("0");
                position0 = (position0 + 1) % k0;
              }
            else
              {
                printf("1");
              }
          }
      }
    return 0;
}
