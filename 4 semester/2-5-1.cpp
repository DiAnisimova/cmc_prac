#include <string>

class BinaryNumber
{
    std::string class_s;
public:
    BinaryNumber(const std::string &s): class_s(s) {}
    operator std::string () const
    {
        return class_s;
    }
    const BinaryNumber &operator++()
    {
        int len = class_s.length();
        bool flag = true;
        for (int i = len - 1; i >= 0 && flag; --i) {
            if (class_s[i] == '0') {
                class_s[i] = '1';
                flag = false;
            } else {
                class_s[i] = '0';
            }
        }
        if (flag) {
            class_s = "1" + class_s;
        }
        return *this;
    }
};
