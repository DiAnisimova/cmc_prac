#include <iostream>
#include <map>

int main()
{
    constexpr unsigned MOD = 4294967161;
    std::map <std::pair<unsigned, unsigned>, unsigned long long> matr;
    bool matr1 = true;
    unsigned R, C; 
    unsigned long long V;
    while (std::cin >> R >> C >> V) {
        if (R == 0 && C == 0 && V == MOD) {
            matr1 = false;
            continue;
        }
        if (matr1) {
            matr.insert({{R, C}, V});
        } else {
            if (!matr.count({R, C})) {
                matr.insert({{R, C}, V});
            } else {
                matr[{R, C}] = (matr[{R, C}] + V) % MOD;
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
            
