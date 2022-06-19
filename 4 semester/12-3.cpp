#include <iostream>

class Result
{
public:
    long long sum = 0;
    Result(int n, int k) {
        if (n == 0 || k == 0 || n == k) {
            sum = 1;
        } else {
            res = Result(n - 1, k).sum + Result(n - 1, k - 1).sum;
        }
    }
};



void calc_binom(int m, int k, std::function<void (uint64_t) > cb)
{
    Result r(m, k);
    cb(r.sum);
}
