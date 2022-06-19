#include <iostream>
#include <set>
#include <string>

bool find_S(std::string s) {
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == 'S') {
            return true;
        }
    }
    return false;
}

int count(std::string s) {
    int c = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            c++;
        }
    }
    return c;
}

int main()
{
    bool ncf = true, S_eps = false, S_right = false, left = true, right = true, auto_left = true, auto_right = true;
    std::set<std::string> S_A;
    std::string str_l, str_r;
    while (std::cin >> str_l >> str_r) {
        if (str_r == "_") {
            if (str_l != "S") {
                ncf = false;
            } else {
                S_eps = true;
            }
        } else if (find_S(str_r)) {
            S_right = true;
        }

        if (count(str_r) == 1 && str_r[0] >= 'A' && str_r[0] <= 'Z') {
            right = false;
            auto_right = false;
            if (str_r.length() > 2) {
                auto_left = false;
            } else if (str_r.length() < 2) {
                if (str_l != "S") {
                    auto_left = false;
                } else if (str_r != "_") {
                    S_A.insert(str_r);
                }
            }
        } else if (count(str_r) >= 1) {
            left = false;
            auto_left = false;
        }

        if (right && count(str_r) == 1 && str_r[str_r.length() - 1] >= 'A' && str_r[str_r.length() - 1] <= 'Z') {
            left = false;
            auto_left = false;
            if (str_r.length() > 2) {
                auto_right = false;
            } else if (str_r.length() < 2) {
                if (str_l != "S") {
                    auto_right = false;
                } else if (str_r != "_") {
                    S_A.insert(str_r);
                }
            }
        } else if (count(str_r) >= 1) {
            right = false;
            auto_right = false;
        }
    }

    //std::cout << ncf << std::endl << S_eps << std::endl << 
    //S_right << std::endl << left << std::endl << right << 
    //std::endl << auto_left << std::endl << auto_right << std::endl;
    if (auto_left && ((S_eps && S_A.size() == 1) || !S_eps)) {
        std::cout << "311" << std::endl;
        return 0;
    }
    if (auto_right && ((S_eps && S_A.size() == 1) || !S_eps)) {
        std::cout << "321" << std::endl;
        return 0;
    }
    if (left) {
        std::cout << "31" << std::endl;
        return 0;
    }
    if (right) {
        std::cout << "32" << std::endl;
        return 0;
    }
    if (S_right && S_eps) {
        ncf = false;
    }
    if (ncf) {
        std::cout << "21" << std::endl;
        return 0;
    }
    std::cout << "2" << std::endl;
    return 0;
}
