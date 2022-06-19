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
    T s_row{};
    if (T_abs(z1.row - z2.row) < T_abs(size.row - T_abs(z1.row - z2.row))) {
        s_row += T_abs(z1.row - z2.row);
    } else {
        s_row += T_abs(size.row - T_abs(z1.row - z2.row));
    }
    T s_col{};
    if (T_abs(z1.col - z2.col) < T_abs(size.col - T_abs(z1.col - z2.col))) {
        s_col += T_abs(z1.col - z2.col);
    } else {
        s_col += T_abs(size.col - T_abs(z1.col - z2.col));
    }
    if (s_row <= s_col) {
        return s_col;
    } else {
        return s_row;
    }
}
