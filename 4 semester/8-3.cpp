#include <iostream>

namespace Game
{
    template <typename T>
    class Coord
    {
    public:
        typedef T value_type;
        T row, col;
        Coord(T x = {}, T y = {}): row(x), col(y) {};
    };
    template <typename T>
    T T_abs(T obj)
    {
        if (obj >= 0) {
            return obj;
        } else {
            return -obj;
        }
    }
    template <typename T>
    T dist(Coord<T> size, Coord<T> z1, Coord<T> z2)
    {
        T dx = T_abs(z1.col - z2.col);
        T dy = T_abs(z1.row - (z1.col + 1) / 2 - (z2.row - (z2.col + 1) / 2));
        T dz = T_abs(z1.col + z1.row - (z1.col + 1) / 2 - (z2.col + z2.row - (z2.col + 1) / 2));
        if (dx >= dy && dx >= dz) {
            return dx;
        }
        if (dy >= dx && dy >= dz) {
            return dy;
        }
        return dz;
    }
};
