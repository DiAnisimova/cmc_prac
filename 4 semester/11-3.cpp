#include <iostream>
#include <vector>
#include <set>
#include <map>

int main()
{
    std::string cur, new_s, end, begin, dest;
    char c;
    std::map<std::string, std::vector<std::pair<char, std::string>>> D;
    std::set<std::string> ends;
    std::cin >> cur;
    while (cur != "END") {
        std::cin >> c >> new_s;
        if (D.find(cur) != D.end()) {
            D[cur].push_back({c, new_s});
        } else {
            D.insert({cur, {{c, new_s}}});
        }
        std::cin >> cur;
    }
    std::cin >> end;
    while (end != "END") {
        ends.insert(end);
        std::cin >> end;
    }
    std::cin >> begin;
    std::cin >> dest;
    std::string cur_st = begin;
    unsigned i;
    bool in_D = false;
    bool flag;
    for (i = 0; i < dest.length(); i++) {
        flag = false;
        for (unsigned j = 0; j < D[cur_st].size(); j++) {
            if (D[cur_st][j].first == dest[i]) {
                flag = true;
                cur_st = D[cur_st][j].second;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    if (flag && (ends.find(cur_st) != ends.end())) {
        in_D = true;
    }
    if (in_D) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }
    std::cout << i << std::endl << cur_st << std::endl;
    return 0;
}
