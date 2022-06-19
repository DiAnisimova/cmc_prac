#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    int r = 0;
    int a;
    for (int i = 0; i < N; i++)
      {
        scanf("%d", &a);
        r = r ^ a;
      }
    printf("%d", r);
    return 0;
}
