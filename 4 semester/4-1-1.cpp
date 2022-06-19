#include <iostream>
#include <vector>

void process(const std::vector<unsigned long long> &v1, std::vector<unsigned long long> &v2, int step)
{
    std::vector<unsigned long long>::const_iterator p1 = v1.begin();
    std::vector<unsigned long long>::reverse_iterator p2 = v2.rbegin();
    while (p1 < v1.end() && p2 < v2.rend()) {
        *p2 += *p1;
        p1 += step;
        p2++;
    }
}
