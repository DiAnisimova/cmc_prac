#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define a4 0.5
#define b4 1.5
#define a5 0.5
#define b5 1.5
#define a6 0.3
#define b6 1.5
#define eps 0.001
#define a1 4
#define b1 5.5
#define a2 0.5
#define b2 2.3
#define a3 3.5
#define b3 4.7
extern double integral(double (*f)(double), double a, double b, double eps2);
extern double root(double (*f)(double), double (*g)(double), double a, double b, double eps1, double (*df)(double), double (*dg)(double));
extern double f1(double);
extern double f2(double);
extern double f3(double);
extern double f4(double);
extern double f5(double);
extern double f6(double);
extern double df1(double);
extern double df2(double);
extern double df3(double);
extern double df4(double);
extern double df5(double);
extern double df6(double);

int rootit(double (*f)(double), double (*g)(double), double a, double b, double eps1, double (*df)(double), double (*dg)(double))
{
    double x = 0;
    int it = 0;
    if ((f(a) - g(a)) < 0 && ((f((a + b) / 2) - g((a + b) / 2)) < (f(a) - g(a) + f(b) - g(b))/2))
      {
        x = b - (f(b) - g(b))/(df(b) - dg(b));
        while ((f(x) - g(x)) * (f(x - eps1) - g(x - eps1)) > 0)
          {
            x = x - (f(x) - g(x))/(df(x) - dg(x));
            it++;
          }
       }
     else if ((f(a) - g(a)) > 0 && ((f((a + b) / 2) - g((a + b) / 2)) > (f(a) - g(a) + f(b) - g(b))/2))
      {
        x = b - (f(b) - g(b))/(df(b) - dg(b));
        while ((f(x) - g(x)) * (f(x - eps1) - g(x - eps1)) > 0)
          {
            x = x - (f(x) - g(x))/(df(x) - dg(x));
            it++;
          }
      }
    else
      {
        x = a - (f(a) - g(a))/(df(a) - dg(a));
        while ((f(x) - g(x)) * (f(x + eps1) - g(x + eps1)) > 0)
          {
            x = x - (f(x) - g(x))/(df(x) - dg(x));
            it++;
          }
      }
    return it;
}
void testintegral(void)
{
    printf("Введите номер функции\n");
    printf("1: 3(0.5/(x + 1) + 1)\n");
    printf("2: 2.5x - 9.5\n");
    printf("3: 5 / x\n");
    printf("4: 10ln(x)\n");
    printf("5: -x^3\n");
    printf("6: - 1/sqrt(x + 8)\n");
    int num;
    double l, r;
    scanf("%d", &num);
    printf("Введите пределы интегрирования\n");
    scanf("%lf%lf", &l, &r);
    double eps2 = eps / 100;
    double integr;
    switch(num){
         case (1):
           integr = integral(f1, l, r, eps2);
           printf("Интеграл равен %lf\n", integr);
           break;
         case (2):
           integr = integral(f2, l, r, eps2);
           printf("Интеграл равен %lf\n", integr);
           break;
         case (3):
           integr = integral(f3, l, r, eps2);
           printf("Интеграл равен %lf\n", integr);
           break;
         case (4):
           if (r <= 0 && l <= 0)
             {
               printf("Функция не определена на этом промежутке\n");
               break;
             }
           if (r <= 0)
             {
               integr = integral(f4, l, 0, eps2);
               printf("Интеграл равен %lf\n", integr);
               break;
             }
           if (l <= 0)
             {
               integr = integral(f4, 0, r, eps2);
               printf("Интеграл равен %lf\n", integr);
               break;
             }
           integr = integral(f4, l, r, eps2);
           printf("Интеграл равен %lf\n", integr);
           break;
         case (5):
           integr = integral(f5, l, r, eps2);
           printf("Интеграл равен %lf\n", integr);
           break;
         case (6):
           if (l <= -8 && r <= -8)
             {
               printf("Функция не определена на этом промежутке\n");
               break;
             }
           if (l <= -8)
             {
               integr = integral(f6, -8, r, eps2);
               printf("Интеграл равен %lf\n", integr);
               break;
             }
           if (r <= -8)
             {
               integr = integral(f6, l, -8, eps2);
               printf("Интеграл равен %lf\n", integr);
               break;
             }
           integr = integral(f6, l, r, eps2);
           printf("Интеграл равен %lf\n", integr);
           break;
      }
}

void testroot(void)
{
    printf("Введите номер уравнения\n");
    printf("1: 3(0.5/(x + 1) + 1) - 2.5x + 9.5 = 0\n");
    printf("2: 3(0.5/(x + 1) + 1) - 5 / x = 0\n");
    printf("3: 2.5x - 9.5 - 5 / x = 0\n");
    printf("4: 10ln(x) + x^3 = 0\n");
    printf("5: 10ln(x) + 1/sqrt(x+8) = 0\n");
    printf("6: x^3 - 1/sqrt(x + 8) = 0\n");
    int num;
    double x;
    int it;
    double eps1 = eps / 100;
    scanf("%d", &num);
    switch(num){
      case (1):
        x = root(f1, f2, a1, b1, eps1, df1, df2);
        break;
      case (2):
        x = root(f1, f3, a2, b2, eps1, df1, df3);
        break;
      case (3):
        x = root(f2, f3, a3, b3, eps1, df2, df3);
        break;
      case (4):
        x = root(f4, f5, a4, b4, eps1, df4, df5);
        break;
      case (5):
        x = root(f4, f6, a5, b5, eps1, df4, df6);
        break;
      case (6):
        x = root(f6, f5, a6, b6, eps1, df6, df5);
        break;
      }
    printf("x = %lf\n", x);
    switch(num){
      case (1):
        it = rootit(f1, f2, a1, b1, eps1, df1, df2);
        break;
      case (2):
        it = rootit(f1, f3, a2, b2, eps1, df1, df3);
        break;
      case (3):
        it = rootit(f2, f3, a3, b3, eps1, df2, df3);
        break;
      case (4):
        it = rootit(f4, f5, a4, b4, eps1, df4, df5);
        break;
      case (5):
        it = rootit(f4, f6, a5, b5, eps1, df4, df6);
        break;
      case (6):
        it = rootit(f6, f5, a6, b6, eps1, df6, df5);
        break;
      }
    printf("Количество итераций = %d\n", it);
}


void test(int argc, int i, char **argv)
{
    if (argc - 1 == i)
      {
        printf("После -test должно идти имя функции: root или integral. Введите заново.\n");
      }
    else if (!strncmp("root", argv[i + 1], 4))
      {
        testroot();
      }
    else if (!strncmp("integral", argv[i + 1], 8))
      {
        testintegral();
      }
}

