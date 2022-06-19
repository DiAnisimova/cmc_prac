// L = {a^(n+1) 0^m b^(n+1) 1^m | n >= 0, m >= 1}

#include <iostream>

char in_l(char c)
{
    int n = 0;
    while (c == 'a') {
        n++;
        c = getchar();
    }
    if (n == 0) {
        std::cout << '0' << std::endl;
        return c;
    }
    int m = 0;
    while (c == '0') {
        m++;
        c = getchar();
    }
    if (m == 0) {
        std::cout << '0' << std::endl;
        return c;
    }
    int count_b = 0;
    while (c == 'b') {
        count_b++;
        c = getchar();
    }
    int count_1 = 0;
    while (c == '1') {
        count_1++;
        c = getchar();
    }
    if ((c != EOF && !isspace(c)) || count_b != n || count_1 != m) {
        std::cout << '0' << std::endl;
        return c;
    }
    std::cout << '1' << std::endl;
    return c;
}

int main()
{
    char c = getchar();
    while (c != EOF) {
        if (isspace(c)) {
            while (isspace(c)) {
                c = getchar();
            }
        }
        if (c == EOF) {
            break;
        }
        c = in_l(c);
        while (!isspace(c) && c != EOF) {
            c = getchar();
        }
    }
    return 0;
}
