#include <iostream>
#include <cmath>

namespace numbers {
    class complex_stack
    {
        complex *ptr = nullptr;
        size_t used;
    public:
        complex_stack(size_t u = 0) : used(u)
        {
            if (used) {
                ptr = new complex[used];
            }
        }
        complex_stack(const complex_stack &v) : used(v.used)
        {
            if (ptr) {
                delete [] ptr;
            }
            ptr = new complex[used];
            for(size_t i = 0; i < used; ++i) {
                ptr[i] = v.ptr[i];
            }
        }
        ~complex_stack() 
        { 
            if (ptr) {
                delete[] ptr; 
            }
        }
        size_t size() const { return used; }
        complex operator[](int i) const { return ptr[i]; }
        complex_stack operator<<(complex c) const
        {
            complex_stack new_stack(used + 1);
            for (size_t i = 0; i < used; ++i) {
                new_stack.ptr[i] = ptr[i];
            }
            new_stack.ptr[used] = c;
            return new_stack;
        }
        complex operator+() const { return ptr[used - 1]; }
        complex_stack &operator=(const complex_stack &v)
        {
            if (&v != this) {
                if (ptr) {
                    delete[] ptr;
                }
                used = v.used;
                ptr = new complex[used];
                for (size_t i = 0; i < used; ++i) {
                    ptr[i] = v.ptr[i];
                }
            }
            return *this;
        }
        complex_stack operator~() const
        {
            complex_stack new_stack(used - 1);
            for (size_t i = 0; i < used - 1; ++i) {
                new_stack.ptr[i] = ptr[i];
            }
            return new_stack;
        }
    };
};
