#include <iostream>
#include <cmath>

namespace numbers
{
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
};
