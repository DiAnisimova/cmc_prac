#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 129
#define BOARD_WIDTH 8

int main(void)
{
    static unsigned cell[BOARD_WIDTH][BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++)
      {
        for (int j = 0; j < BOARD_WIDTH; j++)
          {
            cell[i][j] = 0;
          }
      }
    char s[MAXLINE];
    scanf("%128s", s);
    unsigned len = strlen(s);
    for (int k = 0; k < len; k += 2)
      {
        unsigned str = s[k] - 'a';
        unsigned col = s[k + 1] - '1';
        cell[str][col] = 1;
            for (int i = 0; i < BOARD_WIDTH; i++)
              {
                for (int j = 0; j < BOARD_WIDTH; j++)
                  {
                    if (((i - str) * (i - str)) <= 1 && ((j - col) * (j - col)) <= 1)
                      {
                        cell[i][j] = 1;
                      }
                  }
              }

      }
    unsigned sum = 0;
    for (int i = 0; i < BOARD_WIDTH; i++)
      {
        for (int j = 0; j < BOARD_WIDTH; j++)
          {
            if (cell[i][j] != 1)
              {
                sum++;
              }
          }
      }
    printf("%u", sum);
    return 0;
}
