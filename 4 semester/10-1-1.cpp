#include <iostream>
#include <string>

int main()
{
    std::string s;
    while (std::cin >> s) {
        int i = 0;
        int l = s.length();
        while (i < l && (s[i] == '3' || s[i] == '4')) {
            i++;
        }
        while (i < l && (s[i] == '1' || s[i] == '2')) {
            i++;
        }
        if (i == l) {
            std::cout << '1' << std::endl;
        } else {
            std::cout << '0' << std::endl;
        }
    }
    return 0;
}
