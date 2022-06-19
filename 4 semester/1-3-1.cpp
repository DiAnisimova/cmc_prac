#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    char s;
    bool begin = true;
    while (std::cin >> std::noskipws >> s) {
        if (s >= '1' && s <= '9' && begin) {
            begin = false;
        } else if (!begin && !(s >= '0' && s <= '9')) {
            begin = true;
        }
        if (!begin || s != '0') {
            std::cout << s;
        } else {
            bool end = false;
            while (s == '0' && !end) {
                if (!(std::cin >> std::noskipws >> s)) {
                    end = true;
                }
            }
            if (end || !(s >= '1' && s <= '9')) {
                std::cout << '0';
                if (!end) {
                    std::cout << s;
                }
            } else {
                std::cout << s;
                begin = false;
            }
        }
    }
    return 0;
}
