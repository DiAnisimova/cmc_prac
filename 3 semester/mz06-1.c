#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void)
{
    enum
    {
        BEGIN = 1900,
        THUR = 4,
        DIV = 3
    };
    int year;
    scanf("%d", &year);
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = year - BEGIN;
    int k = 0;
    int prev = 0;
    int sum = 1;
    for (t.tm_mday = 1; t.tm_year == year - BEGIN; t.tm_mday += sum) {
        timegm(&t);
        if (t.tm_wday == THUR) {
            if (t.tm_mon + 1 == prev) {
                k++;
            } else {
                k = 1;
                prev = t.tm_mon + 1;
            }
            if (sum == 1) {
                sum = 7;
            }
        }
        if (t.tm_wday == THUR && t.tm_mday % DIV != 0 && (k == 2 || k == 4)) {
            printf("%d %d\n", t.tm_mon + 1, t.tm_mday);
        }
    }
    return 0;
}
