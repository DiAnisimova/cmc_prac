#include <iostream>

std::string gen_power(uint32_t power)
{
    std::string poliz;
    if (!power) {
        return "1";
    }
    std::string x;
    for (uint32_t i = 0; i < power; i++) {
        x.push_back('x');
    }
    std::string mult;
    for (uint32_t i = 0; i < power - 1; i++) {
        mult.push_back('*');
    }
    return x + mult;
}
