#include <vector>
#include <iostream>
#include <cstdint>

void process(std::vector<int64_t> &v, int64_t max)
{
    int size = 0;
    //std::vector<int64_t>::reverse_iterator pb = v.rbegin();
    //std::vector<int64_t>::reverse_iterator pe = v.rend();
    for (auto p = v.begin(); p < v.end(); p++) {
        if (*p >= max) {
            size++;
        }
    }
    v.reserve(v.size() + size);
    for (auto p = v.rbegin(); p < v.rend(); p++) {
        if (*p >= max) {
            v.push_back(*p);
        }
    }
}

   
