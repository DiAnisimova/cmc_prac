#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(void)
{
    enum 
    {
        BUF_SIZE = 16,
        MINUS = 1,
        PLUS = 0,
        NO_NUMBER = -1,
        SHIFT = 10
    };
    unsigned long long sum = 0;
    unsigned char buf[BUF_SIZE];
    int bytes;
    int sign = -1;
    unsigned long long number = 0;
    while ((bytes = read(0, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < bytes; i++) {
            if (isspace(buf[i])) {
                if (sign == PLUS) {
                    sum += number;
                } else if (sign == MINUS) {
                    sum -= number;
                }
                sign = NO_NUMBER;
                number = 0;
            } else if (buf[i] == '-') {
                sign = MINUS;
            } else if (buf[i] == '+') {
                sign = PLUS;
            } else if (buf[i] >= '0' && buf[i] <= '9') {
                if (sign == NO_NUMBER) {
                    sign = PLUS;   
                }
                number = number * SHIFT + buf[i] - '0';
            } else {
                fprintf(stderr, "Invalid input\n");
                return 1;
            } 
        }
    }
    printf("%lld\n", (long long)sum); 
    return 0;
}

