#include <iostream>
#include <iomanip>

int main()
{
    unsigned w1, w2, num;
    std::cin >> w1 >> w2;
    unsigned l = 0, dis = 0;
    while (std::cin >> num) {
        for (int i = 0; i < 32; i++) {
            l += (num >> i) & 1;
            dis += !((num >> i) & 1);
        }
    }
    unsigned v = l + dis;
    double min = 0, max = 0;
    if (l <= w2) {
        min = -1;
    } else {
        min = -1.0 + (2.0 * (l - w2)) / v;
    }
    if (dis <= w1) {
        max = 1;
    } else {
        max = -1.0 + (2.0 * (l + w1)) / v;
    }
    std::cout << std::setprecision(10) << min << " " << max << std::endl;
    return 0;
}

