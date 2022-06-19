#include <iostream>

class S
{
    int x = 0;
    bool num = true;
public:
    S() {
        if (!(std::cin >> x)) {
            num = false;
        }
    }
    operator bool() {
        return num;
    }
    S(S &&obj) {
        int y;
        x = obj.x;
        if (std::cin >> y) {
            x += y;
            obj.num = false;
        } else {
            num = false;
        }
    }
    ~S() {
        if (num) {
            std::cout << x << std::endl;
        }
    }
};
