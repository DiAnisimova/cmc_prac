#include <iostream>
#include <vector>

int main()
{
    char c;
    std::vector<std::string> stack;
    while (std::cin >> c) {
        if (c >= 'a' && c <= 'z') {
            std::string s(1, c);
            stack.push_back(s);
        } else {
            std::string s2(stack[stack.size() - 1]);
            std::string s1(stack[stack.size() - 2]);
            std::string op(1, c);
            stack.pop_back();
            stack.pop_back();
            std::string s = "(" + s1 + op + s2 + ")";
            stack.push_back(s);
        }
    }
    std::cout << stack[0] << std::endl;
    return 0;
}
