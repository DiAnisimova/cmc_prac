#include <stdio.h>
#include <stdlib.h>

#define BOARD_WIDTH 8

int main(void)
{
    static unsigned front[BOARD_WIDTH], right[BOARD_WIDTH];
    unsigned max_front, max_right;
    scanf("%u", &front[0]);
    max_front = front[0];
    for (int i = 1; i < BOARD_WIDTH; i++)
      {
        scanf("%u", &front[i]);
        if (front[i] > max_front)
          {
            max_front = front[i];
          }
      }
    scanf("%u", &right[0]);
    max_right = right[0];
    for (int i = 1; i < BOARD_WIDTH; i++)
      {
        scanf("%u", &right[i]);
        if (right[i] > max_right)
          {
            max_right = right[i];
          }
      }
    int sum = 0;
    if (max_right != max_front)
      {
        sum = -1;
      }
    else
      {
        for (int i = 0; i < BOARD_WIDTH; i++)
          {
            for (int j = 0; j < BOARD_WIDTH; j++)
              {
                if (right[i] < front[j])
                  {
                    sum += right[i];
                  }
                else
                  {
                    sum += front[j];
                  }
              }
          }
      }
    printf("%d", sum);
    return 0;
}
