#include <vector>
#include <functional>

template<typename T, typename F>
void myapply(T begin, T end, F f)
{
    for (auto p = begin; p != end; p++) {
        f(*p);
    }
}

template<typename T, typename F>
void myapply(T *begin, T *end, F f)
{
    for (auto p = begin; p != end; p++) {
        f(*p);
    }
}

template<typename T, typename F>
std::vector<std::reference_wrapper<typename T::value_type> > myfilter2(T begin, T end, F pred)
{
    std::vector<std::reference_wrapper<typename T::value_type> > v;
    for (auto p = begin; p != end; p++) {
        if (pred(*p)) {
            v.insert(v.end(), std::ref(*p));
        }
    }
    return v;
}

template<typename T, typename F>
std::vector<std::reference_wrapper<T> > myfilter2(T *begin, T *end, F pred)
{
    std::vector<std::reference_wrapper<T> > v;
    for (auto p = begin; p != end; p++) {
        if (pred(*p)) {
            v.insert(v.end(), std::ref(*p));
        }
    }
    return v;
}
