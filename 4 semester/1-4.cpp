#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    double sum = 0, sqsum = 0;
    double number;
    long long n = 0;
    while (std::cin >> number) {
        sum += number;
        sqsum += number * number;
        n++;
    }
    double average = sum / n;
    std::cout << std::fixed << std::showpoint << std::setprecision(10) << average << std::endl;
    double dev = sqrt((sqsum - 2 * sum * average + average * average * n) / n);
    std::cout << std::fixed << std::showpoint << std::setprecision(10) << dev << std::endl;
    return 0;
}
