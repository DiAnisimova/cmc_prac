#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void)
{
    enum
    {
        YEAR = 25,
        MONTH = 9,
        DAY = 7,
        SECONDS = 60,
        MINUTS = 60,
        HOURS = 24,
        DAYS = 30,
        MONTHS = 12,
        BEGIN = 1900
    };
    struct tm begin;
    memset(&begin, 0, sizeof(begin));
    begin.tm_year = YEAR;
    begin.tm_mday = DAY;
    begin.tm_mon = MONTH;
    unsigned long long sec1 = timegm(&begin);
    long long y, m, d;
    while ((scanf("%lld%lld%lld", &y, &m, &d)) != EOF) {
        struct tm end;
        memset(&end, 0, sizeof(end));
        end.tm_year = y - BEGIN;
        end.tm_mon = m - 1;
        end.tm_mday = d;
        time_t sec2 = timegm(&end);
        unsigned long long sec = sec2 - sec1;
        sec = sec / SECONDS;
        sec /= MINUTS;
        sec /= HOURS;
        time_t dn = sec % DAYS + 1;
        sec /= DAYS;
        time_t mn = sec % MONTHS + 1;
        sec /= MONTHS;
        time_t yn = sec + 1;
        printf("%ld %ld %ld\n", yn, mn, dn);
    }   
    return 0;
}
