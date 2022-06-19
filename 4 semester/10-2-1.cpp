#include <iostream>

char in_l(char c)
{
    int k = 0;
    while (c == '0') {
        k++;
        c = getchar();
    }
    if (k == 0) {
        std::cout << '0' << std::endl;
        return c;
    }
    int m = 0;
    while (c == '1') {
        m++;
        c = getchar();
    }
    if (m == 0) {
        std::cout << '0' << std::endl;
        return c;
    }
    while (c != EOF && !isspace(c)) {
        int cur_k = 0, cur_m = 0;
        while (c == '0') {
            cur_k++;
            c = getchar();
        }
        while (c == '1') {
            cur_m++;
            c = getchar();
        }
        if (cur_k != k || cur_m != m) {
            std::cout << '0' << std::endl;
            return c;
        }
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
