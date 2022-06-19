#include <iostream>
using namespace std;

class A
{
    int number = 0;
    bool two_num = false;
public:
    A() { cin >> number; }
    A(const A &v)
    {
        cin >> number;
        number += v.number;
        two_num = true;
    }
    ~A()
    {
        if (two_num) {
            cout << number << endl;
        }
    }
};
