#include <iostream>
#include <unordered_set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

std::vector<char> update(std::vector<char> &reach, std::string s)
{
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            if ((std::find(reach.begin(), reach.end(), s[i]) == reach.end())) {
                reach.push_back(s[i]);
            }
        }
    }
    return reach;
}

bool check(std::string s, std::vector<char> reach) {
    for (unsigned i = 0; i < s.length(); i++) {
        if ((s[i] >= 'A' && s[i] <= 'Z') && 
            std::find(reach.begin(), reach.end(), s[i]) == reach.end()) {
            return false;
        }
    }
    return true;
}

int main()
{
    std::string right;
    char left;
    std::map<char, std::vector<std::string>> grammar;
    std::vector<char> reach;
    while (std::cin >> left >> right) {
        if (grammar.find(left) == grammar.end()) {
            grammar.insert({left, {right}});
        } else {
            grammar[left].push_back(right);
        }
    }
    reach.push_back('S');
    unsigned size = reach.size();
    for (unsigned i = 0; i < size; i++) {
        if (reach[i] >= 'A' && reach[i] <= 'Z' && (grammar.find(reach[i]) != grammar.end())) {
            for (auto it = grammar[reach[i]].begin(); it != grammar[reach[i]].end(); it++) {
                if (*it != "") {
                    reach = update(reach, *it);
                    size = reach.size();
                }
            }
        }
    }
    for (auto p = grammar.begin(); p != grammar.end(); p++) {
        if (std::find(reach.begin(), reach.end(), p->first) != reach.end()) {
            for (auto it = p->second.begin(); it != p->second.end(); it++) {
                if (check(*it, reach)) {
                    std::cout << p->first << ' ' << *it << std::endl;
                }
            }
        }
    }
    return 0;
}
