#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <cmc_complex.h>
#include <cmc_complex_stack.h>
#include <cmc_complex_eval.h>

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
