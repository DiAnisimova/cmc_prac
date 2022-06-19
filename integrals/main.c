#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define eps 0.001
#define a1 4
#define b1 5.5
#define a2 0.5
#define b2 2.3
#define a3 3.5
#define b3 4.7

extern int rootit(double (*f)(double), double (*g)(double), double a, double b, double eps1, double (*df)(double), double (*dg)(double));
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
extern void test(int argc, int i, char **argv);

void help(void)
{
    printf("Вывод всех ключей: -help\n");
    printf("Вывод абсцисс точек пересечения: -absc\n");
    printf("Вывод количества итераций: -iter\n");
    printf("Тестирование функции: -test <root или integral>\n");
    printf("Вывод искомой площади: -sq\n");
    printf("Вывод ординат точек пересечения: -ord\n");
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1, double (*df)(double), double (*dg)(double))
{
    double x = 0;
    if ((f(a) - g(a)) < 0 && ((f((a + b) / 2) - g((a + b) / 2)) < (f(a) - g(a) + f(b) - g(b))/2))
      {
        x = b - (f(b) - g(b))/(df(b) - dg(b));
        while ((f(x) - g(x)) * (f(x - eps1) - g(x - eps1)) > 0)
          {
            x = x - (f(x) - g(x))/(df(x) - dg(x));
          }
       }
     else if ((f(a) - g(a)) > 0 && ((f((a + b) / 2) - g((a + b) / 2)) > (f(a) - g(a) + f(b) - g(b))/2))
      {
        x = b - (f(b) - g(b))/(df(b) - dg(b));
        while ((f(x) - g(x)) * (f(x - eps1) - g(x - eps1)) > 0)
          {
            x = x - (f(x) - g(x))/(df(x) - dg(x));
          }
      }
    else
      {
        x = a - (f(a) - g(a))/(df(a) - dg(a));
        while ((f(x) - g(x)) * (f(x + eps1) - g(x + eps1)) >= 0)
          {
            x = x - (f(x) - g(x))/(df(x) - dg(x));
          }
      }
    return x;
}

double integral(double (*f)(double), double a, double b, double eps2)
{
    double In, I2 = 0;
    int n = 10;
    double h = (b - a) / n;
    double fi = 0;
    for (int i = 0; i < n; i++)
      {
        fi = f(a + (i + 0.5) * h);
        In += fi;
      }
    In *= h;
    int k = 0;
    while (fabs(In - I2) / 3 >= eps2)
      {
        if (k)
          {
            In = I2;
          }
        n *= 2;
        h = (b - a) / n;
        for (int i = 0; i < n; i++)
          {
            fi = f(a + (i + 0.5) * h);
            I2 += fi;
          }
        I2 *= h;
        k++;
      }
    return I2;
}

int main(int argc, char **argv)
{
    int sq = -1;
    int absc = -1;
    int iter = -1;
    int ord = -1;
    for (int i = 0; i < argc; i++)
      {
        if (!strncmp("-help", argv[i], 5))
          {
            help();
            return 0;
          }
        if (!strncmp("-absc", argv[i], 5))
          {
            absc = 0;
          }
        if (!strncmp("-iter", argv[i], 5))
          {
            iter = 0;
          }
        if (!strncmp("-ord", argv[i], 4))
          {
            ord = 0;
          }
        if (!strncmp("-test", argv[i], 5))
          {
            test(argc, i, argv);
            return 0;
          }
        if (!strncmp("-sq", argv[i], 3))
          {
            sq = 0;
          }
      }
    double x1, x2, x3; //1 - f1,f2; 2 - f2,f3; 3 - f1,f3
    double s, s1, s2,s3;
    double eps1 = eps / 100;
    double eps2 = eps / 100;
    x1 = root(f1, f2, a1, b1, eps1, df1, df2);
    x2 = root(f2, f3, a3, b3, eps1, df2, df3);
    x3 = root(f1, f3, a2, b2, eps1, df1, df3);
    if (!absc)
      {
        printf("x1 = %lf\n", x1);
        printf("x2 = %lf\n", x2);
        printf("x3 = %lf\n", x3);
      }
    if (!iter)
      {
        int it1 = 0, it2 = 0, it3 = 0;
        it1 = rootit(f1, f2, a1, b1, eps1, df1, df2);
        it2 = rootit(f2, f3, a3, b3, eps1, df2, df3);
        it3 = rootit(f1, f3, a2, b2, eps1, df1, df3); 
        printf("Число итераций при поиске x1: %d\n", it1);
        printf("Число итераций при поиске x2: %d\n", it2);
        printf("Число итераций при поиске x3: %d\n", it3);
      }      
    if (!ord)
      {
        double y1, y2, y3;
        y1 = f1(x1);
        y2 = f2(x2);
        y3 = f3(x3);
        printf("y1 = %lf\n", y1);
        printf("y2 = %lf\n", y2);
        printf("y3 = %lf\n", y3);
      }
    s1 = integral(f1, x3, x1, eps2);
    s2 = integral(f2, x2, x1, eps2);
    s3 = integral(f3, x3, x2, eps2);
    s = s1 - s2 - s3;
    if (!sq)
      {
        printf("S = %lf\n", s);
      }
    return 0;
}
