#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

int main()
{
    constexpr unsigned MOD = 4294967161;
    std::map <unsigned,std::map<unsigned, unsigned long long>> matr1;
    std::map<std::pair<unsigned, unsigned>, unsigned long long> matr;
    bool first = true;
    unsigned R, C; 
    unsigned long long V;
    while (std::cin >> R >> C >> V) {
        if (R == 0 && C == 0 && V == MOD) {
            first = false;
            continue;
        }
        if (first) {
            if (V) {
                matr1[C][R] = V;
            }
        } else {
            if (V != 0) {
                if (matr1.find(R) != matr1.end()) {
                    for (auto t = matr1[R].begin(); t != matr1[R].end(); t++) {
                        unsigned long long x = t->first;
                        matr[{x,C}] += (t->second * V) % MOD;
                        matr[{x,C}] %= MOD;
                    }
                }
            }
        }
    }
    for (auto p = matr.begin(); p != matr.end(); p++) {
        if (p->second) {
            std::cout << p->first.first << ' '<< p->first.second << ' ' << p->second << std::endl;
        }
    }
    return 0;
}
