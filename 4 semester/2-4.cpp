#include <iostream>

int main()
{
    constexpr int MAXLEN = 4;
    char c;
    char prev_c = 0;
    int k = 0;
    while (std::cin >> std::noskipws >> c) {
        if (k == 0) {
            prev_c = c;
            k = 1;
        } else if (prev_c == c) {
            k++;
        } else {
            if (prev_c == '#' || k > MAXLEN) {
                std::cout << '#' << prev_c << std::hex << k <<'#';
            } else {
                for (int i = 0; i < k; ++i) {
                    std::cout << prev_c;
                }
            }
            k = 1;
            prev_c = c;
        }
    }
    if (c == '#' || k > MAXLEN) {
        std::cout << '#' << prev_c << std::hex << k << '#';
    } else {
        for (int i = 0; i < k; ++i) {
            std::cout << prev_c;
        }
    }
    return 0;
}

