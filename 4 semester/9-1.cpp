#include <iostream>
#include <string>

class Str
{
    std::string s;
public:
    Str(std::string &s1): s(s1) {};
    ~Str() { std::cout << s << std::endl; }
};

void f() {
    std::string s = "";
    std::cin >> s;
    try {
        if (s != "") {
            throw 0;
        }
    }
    catch(int) {
        f();
        Str obj(s);
    }
}

int main()
{
    f();
    return 0;
}
