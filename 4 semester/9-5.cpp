#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace boost::gregorian;

int main()
{
    unsigned short y, m, d;
    unsigned long long sum = 0;
    char c;
    std::cin >> y >> c >> m >> c >> d;
    date prev{y, m, d};
    while (std::cin >> y >> c >> m >> c >> d) {
        date cur{y, m, d};
        sum += abs((cur - prev).days());
        prev = cur;
    }
    std::cout << sum << std::endl;
    return 0;
}
