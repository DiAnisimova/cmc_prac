#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int cnt_sel_change;
static int cnt_heap_comp;
static int cnt_heap_change;

void make_mas(long long n, int p, long long *arr)
{
    if (p == 1)
      {
        for (long long i = 0; i < n; i++)
          {
            arr[i] = i;
          }
      }
    else if (p == 2)
      {
        for (long long i = 0; i < n; i++)
          {
            arr[i] = n - i;
          }
      }
    else
      {
        srand(time(NULL));
        for (long long i = 0; i < n; i++)
          {
            arr[i] = 0;
            for (int k = 7; k >= 0; k--)
              {
                arr[i] = arr[i] + ((rand() % 256) << (8 * k));
              }
          }
      }
}

void selection_sort(long long n, long long *buf)
{
    for (long long i = 0; i < n - 1; i++)
      {
        long long min_index = i;
        long long min_value = buf[i];
        for (long long j = i + 1; j < n; j++)
          {
            if (buf[j] < buf[min_index])
              {
                min_index = j;
                min_value = buf[min_index];
              }
          }
        if (min_index != i)
          {
            buf[min_index] = buf[i];
            buf[i] = min_value;
            cnt_sel_change++;
          }
      }
}

void sift(long long left, long long right, long long *arr)
{
    long long parent = left;
    long long child = 2 * parent + 1;
    long long curr = arr[parent];
    if (child < right)
      {
        if (arr[child] < arr[child + 1])
          {
            child++;
          }
        cnt_heap_comp++;
      }
    while (child <= right && curr < arr[child])
      {
        cnt_heap_comp++;
        arr[parent] = arr[child];
        cnt_heap_change++;
        parent = child;
        child = 2 * child + 1;
        if (child < right)
          {
            if (arr[child] < arr[child + 1])
              {
                child++;
              }
            cnt_heap_comp++;
          }
      }
    arr[parent] = curr;
}

void heap_sort(long long n, long long *arr)
{
    long long left = n / 2;
    long long right = n - 1;
    while (left > 0)
      {
        left--;
        sift(left, right, arr);
      }
    long long x;
    while (right > 0)
      {
        x = arr[0];
        arr[0] = arr[right];
        arr[right] = x;
        cnt_heap_change++;
        right--;
        sift(left, right, arr);
      }
}

void print_mas(long long n, long long *arr)
{
    for (int i = 0; i < n; i++)
      {
        printf("%lld ", arr[i]);
      }
    printf("\n");
}

int main(void)
{
    long long n;
    int p;
    printf("Введите размер массива: ");
    scanf("%lld", &n);
    printf("Введите параметр генерации массива: ");
    scanf("%d", &p);
    long long int *arr = malloc(n * sizeof(long long));
    long long int *buf = malloc(n * sizeof(long long));
    make_mas(n, p, arr);
    printf("Сгенерированный массив: ");
    print_mas(n, arr);
    for (long long i = 0; i < n; i++)
      {
        buf[i] = arr[i];
      }
    selection_sort(n, buf);
    heap_sort(n, arr);
    printf("Результат сортировки выбором: ");
    print_mas(n, buf);
    printf("Результат пирамидальной сортировки: ");
    print_mas(n, arr);
    printf("Количество обменов в сортировке выбором: %d\n", cnt_sel_change);
    printf("Количество сравнений в пирамидальной сортировке: %d\n", cnt_heap_comp);
    printf("Количество обменов в пирамидальной сортировке: %d", cnt_heap_change);
    free(arr);
    free(buf);
    return 0;
}
