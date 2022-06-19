#include <iostream>
#include <vector>

template <typename T>
class Mul
{
public:
    T operator()(T x, T y)
    {
        return x * y;
    }
};

template <typename T>
class Add
{
public:
    T operator()(T x, T y)
    {
        return x + y;
    }
};

template <typename T1, typename T2, 
typename M = Mul<typename std::iterator_traits<T1>::value_type>,
typename A = Add<typename std::iterator_traits<T1>::value_type>>
typename std::iterator_traits<T1>::value_type scalar_mul(T1 Ibeg, T1 Iend, T2 I2, 
typename std::iterator_traits<T1>::value_type Init = typename std::iterator_traits<T1>::value_type{},
M MulF = Mul<typename std::iterator_traits<T1>::value_type>(), 
A AddF = Add<typename std::iterator_traits<T1>::value_type>())
{
    auto j = I2;
    typename std::iterator_traits<T1>::value_type result = Init;
    for (auto i = Ibeg; i != Iend; ++i, ++j) {
        result = AddF(result, MulF(*i, *j));
    }
    return result;
}
