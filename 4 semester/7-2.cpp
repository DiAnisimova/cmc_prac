#include <string>
#include <cmath>

class Rectangle: public Figure
{
    double a, b;
public:
    Rectangle(double x = 0, double y = 0): a(x), b(y) {}
    static Rectangle *make(std::string s)
    {
        Rectangle *obj = new Rectangle;
        sscanf(s.c_str(), "%lf %lf", &obj->a, &obj->b);
        return obj;
    }
    double get_square() const
    {
        return a * b;
    }
};

class Square: public Figure
{
    double a;
public:
    Square(double x = 0): a(x) {}
    static Square *make(std::string s)
    {
        Square *obj = new Square;
        sscanf(s.c_str(), "%lf", &obj->a);
        return obj;
    }
    double get_square() const
    {
        return a * a;
    }
};

class Circle: public Figure
{
    double r;
public:
    Circle(double x = 0): r(x) {}
    static Circle *make(std::string s)
    {
        Circle *obj = new Circle;
        sscanf(s.c_str(), "%lf", &obj->r);
        return obj;
    }
    double get_square() const
    {
        return M_PI * r * r;
    }
};
