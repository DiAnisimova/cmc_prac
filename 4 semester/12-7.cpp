// a^n c^m e d^m b^n , n>= 1, m >= 0
// c b^n d, n >= 0
// c
// cd

#include <iostream>

char c;

bool gc()
{
    if (std::cin >> c) {
        return true;
    }
    return false;
}

bool A();
bool B();

bool S()
{
    bool flag = gc();
    if (!flag) {
        return false;
    }
    if (c == 'a') {
        return A() && gc() && (c == 'b');
    }
    if (c == 'c') {
        return B();
    }
    return false;
}

bool A()
{
    bool flag = gc();
    if (!flag) {
        return false;
    }
    if (c == 'c') {
        return A() && gc() && (c == 'd');
    }
    if (c == 'e') {
        return true;
    }
    return false;
}

bool B()
{
    bool flag = gc();
    if (flag) {
        return true;
    }
    if (c == 'd') {
        return true;
    }
    if (c == 'b') {
        return B();
    }
    return false;
}

int main()
{
    bool flag1 = S();
    bool flag2 = gc();
    std::cout << (flag1 && !flag2) << std::endl;
    return 0;
}
