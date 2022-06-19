#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float xa, ya, xb, yb, xc, yc;
    scanf("%f%f%f%f%f%f", &xa, &ya, &xb, &yb, &xc, &yc);
    float xd, yd;
    xd = (xa + xb) / 2;
    yd = (ya + yb) / 2;
    float xm, ym;
    xm = (xc + 2 * xd) / 3;
    ym = (yc + 2 * yd) /3;
    printf("%.4f", xm);
    printf(" ");
    printf("%.4f", ym);
    return 0;
}
