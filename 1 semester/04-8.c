#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000


int main(void)
{
    static int number[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
      {
        number[i] = 0;
      }
    char c;
    int x;
    int k = 0;
    while ((c = getchar()) != '\n')
      {
        x = c - '0';

        for (int i = 99; i > 0; i--)
          {
            if (number[i])
              {

                if (10 * i + x > 99 && !(number[10 * i + x]))
                  {
                    k++;
                  }
                number[10 * i + x] = 1;
              }
          }
        number[x] = 1;
      }
    printf("%d", k);
    return 0;
}

