#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10000

int main(void)
{
    unsigned N;
    scanf("%u", &N);
    static int number[MAXSIZE];
    int is_perm = 1;
    for (int i = 0; i < N; i++)
      {
        scanf("%d", &number[i]);
        if (number[i] < 0 || number[i] > N)
          {
            is_perm = 0;
          }
      }
    if (is_perm)
      {
        for (int i = 0; i < (N - 1); i++)
          {
            for (int j = i + 1; j < N; j++)
              {
                if (number[i] == number[j])
                  {
                    is_perm = 0;
                  }
              }
          }
      }
    if (is_perm)
      {
        printf("Yes");
      }
    else
      {
        printf("No");
      }
    return 0;
}
