#include <iostream>
#include <map>
#include <vector>
#include <set>

struct Coord
{
    int x, y, z;
    char edge = 0;
    char type = 'a';
    Coord *z_plus = nullptr;
    Coord *z_minus = nullptr;
    Coord *y_plus = nullptr;
    Coord *y_minus = nullptr;
    Coord *x_plus = nullptr;
    Coord *x_minus = nullptr;
    Coord(int a = 0, int b = 0, int c = 0): x(a), y(b), z(c) {};
};
    

int main()
{
    std::vector<Coord> cube(26);
    int num = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (i != 0 || j != 0 || k != 0) {
                    cube[num] = Coord(i, j, k);
                }
            }
        }
    }
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (i != 0 || j != 0 || k != 0) {
                    if (
                }
            }
        }
    }
