#include <iostream>

bool check_left(std::string s) {
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            return true;
        }
    }
    return false;
}

bool find_S(std::string s) {
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == 'S') {
            return true;
        }
    }
    return false;
}

int main()
{
    std::string left, right;
    int count_S = 0;
    bool grammar = true, cf = true, ncf = true, empty = true, S_right = false, S_eps = false;
    while (std::cin >> left >> right) {
        empty = false;
        if (left == "S") {
            count_S++;
        }
        if (!check_left(left)) {
            grammar = false;
            break;
        }
        if (cf && left.length() > 1) {
            cf = false;
            ncf = false;
        }
        if (ncf) {
            if (right == "_") {
                if (left != "S") {
                    ncf = false;
                } else {
                    S_eps = true;
                }
            } else if (find_S(right)) {
                S_right = true;
            }
        }
    }
    if (count_S == 0 || empty) {
        grammar = false;
    }
    if (!grammar) {
        std::cout << "-1" << std::endl;
        return 0;
    }
    if (S_right && S_eps) {
        ncf = false;
    }
    if (ncf) {
        std::cout << "23" << std::endl;
        return 0;
    }
    if (cf) {
        std::cout << "2" << std::endl;
        return 0;
    }
    std::cout << "10" << std::endl;
    return 0;
}

