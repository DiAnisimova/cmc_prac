#include <iostream>
#include <cstdint>

int main()
{
    constexpr uint32_t N_BYTES = 16;
    constexpr uint32_t SIZE = 4;
    constexpr uint32_t SHIFT = 8;
    uint32_t offset;
    while (std::cin >> std::hex >> offset) {
        uint32_t number = 0;
        uint32_t i = 0;
        uint32_t byte;
        while (i < N_BYTES && std::cin >> std::hex >> byte) {
            number = (number << SHIFT) + byte;
            i++;
            if (i % SIZE == 0) {
                std::cout << number << std::endl;
                number = 0;
            }
        }
    }
    return 0;
}
