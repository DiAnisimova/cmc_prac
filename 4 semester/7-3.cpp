#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <algorithm>
#include <cmath>

class Factory
{
    std::map<char, std::function<std::unique_ptr<Figure> (std::string)> > figures {
        {'R', [](std::string s)
            {
                Rectangle *obj = Rectangle::make(s);
                return std::unique_ptr<Figure>(obj);
            }
        },
        {'S', [](std::string s)
            {
                Square *obj = Square::make(s);
                return std::unique_ptr<Figure>(obj);
            }
        },
        {'C', [](std::string s)
            {
                Circle *obj = Circle::make(s);
                return std::unique_ptr<Figure>(obj);
            }
        }
    };
    Factory() {};
public:
    static Factory factory_instance() {
        static Factory obj;
        return obj;
    }
    std::unique_ptr<Figure> make_fig(std::string s)
    {
        std::istringstream strin(s);
        char type;
        strin >> type;
        std::getline(strin, s);
        return figures[type](s);
    }
};

bool comp(const std::unique_ptr<Figure> &f1, const std::unique_ptr<Figure> &f2)
{
    return f1->get_square() < f2->get_square();
}

int main()
{
    Factory fact = Factory::factory_instance();
    std::vector<std::unique_ptr<Figure>> figures;
    std::string s;
    while (getline(std::cin, s)) {
        figures.push_back(fact.make_fig(s));
    }
    std::stable_sort(figures.begin(), figures.end(), comp);
    for (auto &f: figures) {
        std::cout << f->to_string() << std::endl;
    }
    return 0;
}

