#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 3

int move_Garik(int x0, int y0, int x,int y)
{
  if ((abs(x0 - x) == 2 && abs(y - y0) == 1) ||
      (abs(x0 - x) == 1 && abs(y - y0) == 2))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int move_Tolik(int x0, int y0, int x, int y)
{
  if((x0 - x == 0 && y0 - y != 0) ||
     (x0 - x != 0 && y0 - y == 0) ||
    (abs(x0 - x) == abs(y0 - y) && (x0 - x != 0)))
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

int main(void)
{
  char s[MAX_SIZE];
  scanf("%2s", s);
  int x, y, x0, y0, x1, y1;
  int k = 1;
  x0 = 0;
  y0 = 0;
  x1 = 0;
  y1 = 0;
  int is_right = 1;
  int k_h8 = 0;
  while (s[0] != 'X')
    {
      x = s[0] - 'A';
      y = s[1] - '1';
      if (k % 2 == 1)
        {
          is_right *= move_Garik(x0, y0, x,y);
        }
      else
        {
          is_right *= move_Tolik(x0, y0,x,y);
        }
      if ((x1 - x || y1 - y) == 0)
        {
          is_right = 0;
        }
      if (x == 7 && y == 7)
        {
          k_h8++;
        }
      x1 = x0;
      y1 = y0;
      x0 = x;
      y0 = y;
      scanf("%2s", s);
      k++;
    }
  if (!is_right || x0 != 7 || y0 != 7 || k_h8 != 1)
    {
      printf("Cheaters");
    }
  else if (k % 2 == 1)
    {
      printf("Tolik");
    }
  else
    {
      printf("Garik");
    }
  return 0;
}
