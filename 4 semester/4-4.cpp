#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class Average
{
public:
    double sum = 0.0;
    int count = 0;
    Average(): sum(0.0), count(0) {}
    ~Average() {}
    void operator()(double x)
    {
        sum += x;
        count++;
    }
};

int main()
{
    std::vector<double> v;
    double x;
    while (std::cin >> x) {
        v.push_back(x);
    }
    int num_del = v.size() / 10;
    v.erase(v.begin(), v.begin() + num_del);
    v.erase(v.end() - num_del, v.end());
    std::sort(v.begin(), v.end());
    num_del = v.size() / 10;
    v.erase(v.begin(), v.begin() + num_del);
    v.erase(v.end() - num_del, v.end());
    Average res = std::for_each(v.begin(), v.end(), Average());
    std::cout << std::fixed << std::showpoint << std::setprecision(10) << res.sum / res.count << std::endl;
    return 0;
}
