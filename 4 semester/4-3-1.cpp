#include <iostream>
#include <vector>
#include <algorithm>

void process(const std::vector<int> &v1, std::vector<int> &v2)
{
    std::vector<int> loc_vec(v1.begin(), v1.end());
    std::sort(loc_vec.begin(), loc_vec.end());
    std::vector<int>::iterator end = std::unique(loc_vec.begin(), loc_vec.end());
    int size = v2.size();
    std::vector<int>::iterator cur = v2.begin();
    std::vector<int>::iterator index = loc_vec.begin();
    while (index != end && *index < 0) {
        index++;
    }
    std::vector<int>::iterator p = v2.begin();
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (index != end && i == *index) {
            p++;
            index++;
            count++;
        } else {
            *cur = *p;
            cur++;
            p++;
        }
    }
    if (count == 0) {
        return;
    }
    v2.erase(cur, v2.end());
}
