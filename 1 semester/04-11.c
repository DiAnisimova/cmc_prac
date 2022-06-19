#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2002
#define LEN_NUM 11

long operation(int first, int second, int oper)
{
    if (oper == 1)
      {
        return first + second;
      }
    else if (oper == 2)
      {
        return first - second;
      }
    else if (oper == 3)
      {
        return first * second;
      }
    else if (oper == 4 && second != 0)
      {
        return first / second;
      }
    else return -1;

}

int main(void)
{
    char s[MAX_LEN];
    fgets(s, MAX_LEN - 1, stdin);
    int l = strlen(s);
    char number[LEN_NUM];
    int j = 0;
    int oper = 0;
    int first = -1;
    int second = -1;
    for (int i = 0; i < l; i++)
      {
        if (s[i] >= '0' && s[i] <= '9')
          {
            number[j] = s[i];
            number[j + 1] = '\0';
            j++;
          }
        else if (s[i] == '+' && j != 0)
          {
            if (first == -1)
              {
                first = atoi(number);
                j = 0;
              }
            else
              {
                second = atoi(number);
                j = 0;
                long res = operation(first, second, oper);
                if (res <= 120000 && res != -1)
                  {
                    printf("%d ", first);
                    if (oper == 1)
                      {
                        printf("+ ");
                      }
                    if (oper == 2)
                      {
                        printf("- ");
                      }
                    if (oper == 3)
                      {
                        printf("* ");
                      }
                    if (oper == 4)
                      {
                        printf("/ ");
                      }
                    printf("%d ", second);
                    printf("= ");
                    printf("%ld\n", res);
                  }
                first = second;
                second = -1;
              }
            oper = 1;
          }
        else if (s[i] == '-' && j != 0)
          {
            if (first == -1)
              {
                first = atoi(number);
                j = 0;
              }
            else
              {
                second = atoi(number);
                j = 0;
                long res = operation(first, second, oper);
                if (res <= 120000 && res != -1)
                  {
                    printf("%d ", first);
                    if (oper == 1)
                      {
                        printf("+ ");
                      }
                    if (oper == 2)
                      {
                        printf("- ");
                      }
                    if (oper == 3)
                      {
                        printf("* ");
                      }
                    if (oper == 4)
                      {
                        printf("/ ");
                      }
                    printf("%d ", second);
                    printf("= ");
                    printf("%ld\n", res);
                  }
                first = second;
                second = -1;
              }
            oper = 2;
          }
        else if (s[i] == '*' && j != 0)
          {
            if (first == -1)
              {
                first = atoi(number);
                j = 0;
              }
            else
              {
                second = atoi(number);
                j = 0;
                long res = operation(first, second, oper);
                if (res <= 120000)
                  {
                    printf("%d ", first);
                    if (oper == 1)
                      {
                        printf("+ ");
                      }
                    if (oper == 2)
                      {
                        printf("- ");
                      }
                    if (oper == 3)
                      {
                        printf("* ");
                      }
                    if (oper == 4)
                      {
                        printf("/ ");
                      }
                    printf("%d ", second);
                    printf("= ");
                    printf("%ld\n", res);
                  }
                first = second;
                second = -1;
              }
            oper = 3;
          }
        else if (s[i] == '/' && j != 0)
          {
            if (first == -1)
              {
                first = atoi(number);
                j = 0;
              }
            else
              {
                second = atoi(number);
                j = 0;
                long res = operation(first, second, oper);
                if (res <= 120000 && res != -1)
                  {
                    printf("%d ", first);
                    if (oper == 1)
                      {
                        printf("+ ");
                      }
                    if (oper == 2)
                      {
                        printf("- ");
                      }
                    if (oper == 3)
                      {
                        printf("* ");
                      }
                    if (oper == 4)
                      {
                        printf("/ ");
                      }
                    printf("%d ", second);
                    printf("= ");
                    printf("%ld\n", res);
                  }
                first = second;
                second = -1;
              }
            oper = 4;
          }
        else
          {
            if (j != 0 && first != -1)
              {
                second = atoi(number);
                j = 0;
                long res = operation(first, second, oper);
                if (res <= 120000 && res != -1)
                  {
                    printf("%d ", first);
                    if (oper == 1)
                      {
                        printf("+ ");
                      }
                    if (oper == 2)
                      {
                        printf("- ");
                      }
                    if (oper == 3)
                      {
                        printf("* ");
                      }
                    if (oper == 4)
                      {
                        printf("/ ");
                      }
                    printf("%d ", second);
                    printf("= ");
                    printf("%ld\n", res);
                  }
                first = second;
                second = -1;
              }
            else
              {
                second = -1;
                first = -1;
                j = 0;
              }
            oper = 0;
          }
      }
    return 0;
}
