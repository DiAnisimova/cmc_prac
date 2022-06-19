//S->aAd 
//A->aAd | bBc 
//B->bBc | ε

#include <iostream>

void B(int k)
{
    if (k == 0) {
        return;
    }
    std::cout << 'b';
    B(k - 1);
    std::cout << 'c';
}

void A(int cur, int k) 
{
    if (cur == 0) {
        std::cout << 'b';
        B(k);
        std::cout << 'c';
        return;
    }
    std::cout << 'a';
    A(cur - 1, k);
    std::cout << 'd';
}

void S(int cur, int k) 
{
    std::cout << 'a';
    A(cur - 2, k - cur);
    std::cout << 'd' << std::endl;
    if (cur > 2) {
        S(cur - 1, k);
    }
}

int main()
{
    int k;
    std::cin >> k;
    if (k % 2 || k < 4) {
        return 0;
    }
    S(k / 2, k / 2);
    return 0;
}
