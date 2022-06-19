#include <iostream>
#include <cstdint>

namespace Sample
{
    template <typename T, const size_t rows, const size_t col>
    class Matrix 
    {
        T matr[rows][col];
    public:
        T* operator[](uint64_t r) {
            return matr[r];
        }
    };
};
