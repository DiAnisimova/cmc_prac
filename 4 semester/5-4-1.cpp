#include <iostream>
#include <vector>
#include <algorithm>

template <typename It1, typename It2>
It2 myremove(It1 begin_v1, It1 end_v1, It2 begin_v2, It2 end_v2)
{
    std::vector<int> loc_vec(begin_v1, end_v1);
    std::sort(loc_vec.begin(), loc_vec.end());
    std::vector<int>::iterator end = std::unique(loc_vec.begin(), loc_vec.end());
    It2 cur = begin_v2;
    std::vector<int>::iterator index = loc_vec.begin();
    while (index != end && *index < 0) {
        index++;
    }
    int count = 0;
    int i = 0;
    for (auto p = begin_v2; p != end_v2; p++, i++) {
        if (index != end && i == *index) {
            index++;
            count++;
        } else {
            *cur = std::move(*p);
            cur++;
        }
    }
    if (count == 0) {
        return end_v2;
    }
    return cur;
}
