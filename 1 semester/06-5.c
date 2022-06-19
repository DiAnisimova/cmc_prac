#include <stdio.h>
#include <stdlib.h>

long long operation(long long x, long long y, int oper)
{
    if (oper > 0)
      {
        return x + y;
      }
    return x - y;
}

int main(void)
{
    FILE *f = fopen("input.txt", "r");
    long long last_numb = 0, first_numb = 0;
    int oper = 0;
    char c;
    while ((c = fgetc(f)) != EOF)
      {
        if (c >= '0' && c <= '9')
          {
            last_numb *= 10;
            last_numb += c - '0';
          }
        else if (c == '+' || c == '-')
          {
            if (oper != 0)
              {
                first_numb = operation(first_numb, last_numb, oper);
              }
            else
              {
                first_numb = last_numb;
              }
            last_numb = 0;
            if (c == '+')
              {
                oper = 1;
              }
            else
              {
                oper = -1;
              }
          }
      }
    if (oper)
      {
        first_numb = operation(first_numb, last_numb, oper);
      }
    fclose(f);
    FILE *f1 = fopen("output.txt", "w");
    fprintf(f1, "%lld", first_numb);
    fclose(f1);
    return 0;
}
