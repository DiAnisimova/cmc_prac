template <typename T>
typename T::value_type process(const T &t)
{
    typename T::value_type s = {};
    int i = 0;
    for (auto p = t.rbegin(); i < 5 && p != t.rend(); ++p) {
        if (i % 2 == 0) {
            s += *p;
        }
        i++;
    }
    return s;
}
