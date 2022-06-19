// В try-блоке функция f проверяет условия 
//на k и b, в зависимости от них 
// создает новый объект класса Result. 
//В catch-обработчике функция меняет 
// переданный ей по ссылке объект, 
//записывая в поле sum результат работы функции.

#include <iostream>

class Result
{
public:
    long long  sum = 0;
    Result(long long s): sum(s) {};
};

void f(unsigned long long a, unsigned long long b, unsigned k)
{
    if (k > 0 && b > 1) {
        try {
            f(a, b - 1, k);
        }
        catch (Result &p) {
            f(a, p.sum, k - 1);
        }
    } else if (k > 0 && b == 1) {
        throw Result(a);
    } else if (k == 0) {
        throw Result(a + b);
    }
}

int main()
{
    long long a, b;
    unsigned k;
    while (std::cin >> a >> b >> k) {
        try {
            f(a, b, k);
        }
        catch (Result &r) {
            std::cout << r.sum << std::endl;
        }
    }
    return 0;
}
