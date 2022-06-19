#include <complex>
#include <vector>
#include <array>
#include <iostream>

namespace Equations {
    template <typename T>
    std::pair<bool, std::vector<std::complex<T>>> quadratic(std::array<std::complex<T>,3> v)
    {
        std::complex<T> zero(0,0), c(v[0]), b(v[1]), a(v[2]);
        std::pair<bool, std::vector<std::complex<T>>> res;
        if (a == zero && b == zero && c == zero) {
            res.first = false;
            return res;
        }
        if (a == zero && b == zero) {
            res.first = true;
            return res;
        }
        if (a == zero) {
            res.first = true;
            res.second.push_back(-c / b);
            return res;
        }
        res.first = true;
        std::complex<T> d = b * b - std::complex<T>(4,0) * a * c;
        std::complex<T> root1(-b - sqrt(d));
        root1 /= (std::complex<T>(2,0) * a);
        std::complex<T> root2(-b + sqrt(d));
        root2 /= (std::complex<T>(2,0) * a);
        res.second.push_back(root1);
        res.second.push_back(root2);
        return res;
    }
};
