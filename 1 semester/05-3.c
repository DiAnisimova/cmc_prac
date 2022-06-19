#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr = malloc(sizeof(int));
    int curr_size = 1;
    int buf_size = 0;
    int x;
    scanf("%d", &x);
    while (x != 0)
      {
        buf_size++;
        if (buf_size > curr_size)
          {
            arr = realloc(arr, 3 * curr_size * sizeof(int));
            curr_size *= 3;
          }
        arr[buf_size - 1] = x;
        scanf("%d", &x);
      }
    for (int i = 0; i < buf_size; i += 2)
      {
        printf("%d ", arr[i]);
      }
    for (int i = 1; i < buf_size; i += 2)
      {
        printf("%d ", arr[i]);
      }
    free(arr);
    return 0;
}
