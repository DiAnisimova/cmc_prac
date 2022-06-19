#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 81

int main(void)
{
    char s[L];
    char s1[L];
    int n;
    scanf("%d", &n);
    scanf("%80s", s);
    int l = strlen(s);
    n %= l;
    for (int i = 0; i < l; i++)
      {
        s1[(l + i - n) % l] = s[i];
      }
    s1[l] = '\0';
    printf("%s", s1);
    return 0;
}
