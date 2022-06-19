template <typename T, typename F>
T myfilter(const T &t, F pred)
{
    T new_obj = {};
    for (auto p = t.begin(); p != t.end(); p++) {
        if (pred(*p)) {
            new_obj.insert(new_obj.end(), *p);
        }
    }
    return new_obj;
}

