#include <iostream>
#include <cmath>
#include <vector>
#include <map>

namespace numbers {
    constexpr int MAXSIZE = 1024;
    class complex
    {
        double c_real = 0, c_im = 0;
    public:
        complex(double n_real = 0, double n_im = 0): c_real(n_real), c_im(n_im) {}
        explicit complex(std::string s) {
            sscanf(s.c_str(), "(%lf,%lf)", &c_real, &c_im);
        }
        double re() const { return c_real; }
        double im() const { return c_im; }
        double abs2() const { return c_real * c_real + c_im * c_im; }
        double abs() const { return sqrt(abs2()); }
        std::string to_string() const {
            char s[MAXSIZE];
            snprintf(s, sizeof(s), "(%.10g,%.10g)", c_real, c_im);
            return std::string(s);
        }
        const complex & operator+=(const complex & c)
        {
            c_real += c.re();
            c_im += c.im();
            return *this;
        }
        const complex & operator-=(const complex & c)
        {
            c_real -= c.re();
            c_im -= c.im();
            return *this;
        }
        const complex & operator*=(const complex &c)
        {
            double tmp = c_real;
            c_real = c_real * c.re() - c_im * c.im();
            c_im = c_im * c.re() + tmp * c.im();
            return *this;
        }
        const complex & operator/=(const complex &c)
        {
            double tmp = c_real;
            c_real = (c_real * c.re() + c_im * c.im()) / (c.re() * c.re() + c.im() * c.im());
            c_im = (c_im * c.re() - tmp * c.im()) / (c.re() * c.re() + c.im() * c.im());
            return *this;
        }
        const complex operator~() const
        {
            return complex(c_real, -c_im);
        }
        const complex operator-() const
        {
            return complex(-c_real, -c_im);
        }
    };
    complex operator+(const complex &n1, const complex &n2)
    {
        complex n3(n1.re(), n1.im());
        n3 += n2;
        return n3;
    }
    complex operator-(const complex &n1, const complex &n2)
    {
        complex n3(n1.re(), n1.im());
        n3 -= n2;
        return n3;
    }
    complex operator*(const complex &n1, const complex &n2)
    {
        complex n3(n1.re(), n1.im());
        n3 *= n2;
        return n3;
    }
    complex operator/(const complex &n1, const complex &n2)
    {
        complex n3(n1.re(), n1.im());
        n3 /= n2;
        return n3;
    }



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
        complex_stack &operator=(const complex_stack& v)
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


    complex eval(const std::vector<std::string> &args, const complex &z)
    {
        complex_stack st;
        std::map <char, void(*)(complex_stack &stack)> lambda {
            {'+', [](complex_stack &stack) 
            {
                complex c = +stack;
                stack = ~stack;
                c = c + (+stack);
                stack = ~stack;
                stack = (stack << c);
            }},
            {'-', [](complex_stack &stack)
            {
                complex c1 = +stack;
                stack = ~stack;
                complex c2 = +stack;
                stack = ~stack;
                complex c = c2 - c1;
                stack = (stack << c);
            }},
            {'*', [](complex_stack &stack)
            {
                complex c1 = +stack;
                stack = ~stack;
                complex c2 = +stack;
                stack = ~stack;
                complex c = c1 * c2;
                stack = (stack << c);
            }},
            {'/', [](complex_stack &stack)
            {
                complex c1 = +stack;
                stack = ~stack;
                complex c2 = +stack;
                stack = ~stack;
                complex c = c2 / c1;
                stack = stack << c;
            }},
            {'!', [](complex_stack &stack)
            {
                stack = (stack << (+stack));
            }},
            {';', [](complex_stack &stack)
            {
                stack = ~stack;
            }},
            {'~', [](complex_stack &stack)
            {
                complex c = ~(+stack);
                stack = ~stack;
                stack = (stack << c);
            }},
            {'#', [](complex_stack &stack)
            {
                complex c = -(+stack);
                stack = ~stack;
                stack = (stack << c);
            }}
        };
        auto p = args.begin();
        while (p != args.end()) { 
            if (*p == "z") {
                st = st << z;
                ++p;
            } else if ((*p)[0] == '(') {
                complex c(*p);
                st = st << c;
                ++p;
            } else {
                char op = (*p)[0];
                lambda[op](st);
                ++p;
            }
        }
        return +st;
    }
};

int main(int argc, char **argv)
{
    numbers::complex c(argv[1]);
    double r;
    sscanf(argv[2], "%lf", &r);
    int n;
    sscanf(argv[3], "%d", &n);
    std::vector<std::string> v(argv + 4, argv + argc);
    double c_im = c.im();
    double c_re = c.re();
    double angle = 2 * M_PI / n;
    numbers::complex i = 0;
    for (int k = 0; k < n; k++) {
        double x1 = c_re + r * cos(k * angle);
        double y1 = c_im + r * sin(k * angle);
        numbers::complex z_i1(x1, y1);
        double x2 = c_re + r * cos((k + 1) * angle);
        double y2 = c_im + r * sin((k + 1) * angle);
        numbers::complex z_i2(x2, y2);
        i += (numbers::eval(v, (z_i1 + z_i2) / 2) * (z_i1 - z_i2));
    }
    std::cout << i.to_string() << std::endl;
    return 0;
}
