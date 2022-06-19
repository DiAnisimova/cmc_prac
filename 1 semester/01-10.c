#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned short a, b, c, d;
    scanf("%hu%hu%hu%hu", &a, &b, &c, &d);
    int x;
    x = a + 256 * b + 256 * 256 * c + 256 * 256 * 256 * d;
    printf("%d", x);
    return 0;
}
