#include <iostream>

int main()
{
    int m, n;
    std::cin >> m >> n;
    int r1, c1, r2, c2;
    while (std::cin >> r1 >> c1 >> r2 >> c2) {
        int s = 0;
        if (abs(r1 - r2) < abs(m - abs(r1 - r2))) {
            s = abs(r1 - r2);
        } else {
            s = abs(m - abs(r1 - r2));
        }
        if (abs(c1 - c2) < abs(n - abs(c1 - c2))) {
            s += abs(c1 - c2);
        } else {
            s += abs(n - abs(c1 - c2));
        }
        std::cout << s << std::endl;
    }
    return 0;
}
