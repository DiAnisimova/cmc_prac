#include <iostream>
#include <cstdint>
#include <vector>

void process(std::vector<uint64_t> &v, uint32_t s)
{
    uint64_t sum = 0;
    uint32_t j = 0;
    for (uint32_t i = 0; i < v.size(); i++, j++) {
        sum += v[i];
        if (j && !(j % s)) {
            v.insert(v.begin() + i, sum - v[i]);
            i++;
        }
    }
}
