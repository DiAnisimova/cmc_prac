#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>

struct Point
{
    uint32_t x = 0, y = 0;
    Point(uint32_t a = 0, uint32_t b = 0): x(a), y(b) {}
    ~Point() {}
};

Point max(std::vector<std::vector<uint32_t> > vect)
{
    unsigned max_i = 0, max_j = 0;
    uint32_t max_num = 0;
    for (unsigned  i = 0; i < vect.size(); i++) {
        for (unsigned j = 0; j < vect[i].size(); j++) {
            if (vect[i][j] > max_num) {
                max_num = vect[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    Point z(max_i, max_j);
    return z;
}

int main()
{
    std::vector<std::vector<uint32_t> > v;
    std::string cur_s;
    std::getline(std::cin, cur_s);
    while (cur_s != "") {
        std::vector<uint32_t> curv;
        bool is_number = true;
        int count = 0;
        uint32_t x = 0;
        for (unsigned i = 0; i < cur_s.length(); ++i) {
            if (cur_s[i] == ' ' && is_number) {
                curv.push_back(x);
                count++;
                x = 0;
                is_number = false;
            } else {
                is_number = true;
                x = x * 10 + cur_s[i] - '0';
            }
        }
        curv.push_back(x);
        v.push_back(curv);
        std::getline(std::cin, cur_s);
    }

    std::vector<uint32_t> modif;
    uint32_t x;
    while (std::cin >> x) {
        modif.push_back(x);
    }
    std::sort(modif.begin(), modif.end());

    for (auto p = modif.rbegin(); p != modif.rend(); p++) {
        Point z = max(v);
        if (v[z.x][z.y] >= *p) { // center
            v[z.x][z.y] -= *p;
        } else {
            v[z.x][z.y] = 0;
        }

        if (z.x > 0) { // side 
            if (z.y < v[z.x - 1].size()) {
                if (v[z.x - 1][z.y] >= (*p) / 2) {
                    v[z.x - 1][z.y] -= (*p) / 2;
                } else {
                    v[z.x - 1][z.y] = 0;
                }
            }
        }

        if (z.x < v.size() - 1) { // side
            if (z.y < v[z.x + 1].size()) {
                if (v[z.x + 1][z.y] >= (*p) / 2) {
                    v[z.x + 1][z.y] -= (*p) / 2;
                } else {
                    v[z.x + 1][z.y] = 0;
                }
            }
        }

        if (z.y > 0) { // side
            if (v[z.x][z.y - 1] >= (*p) / 2) {
                v[z.x][z.y - 1] -= (*p) / 2;
            } else {
                v[z.x][z.y - 1] = 0;
            }
        }

        if (z.y < v[z.x].size() - 1) { // side
            if (v[z.x][z.y + 1] >= (*p) / 2) {
                v[z.x][z.y + 1] -= (*p) / 2;
            } else {
                v[z.x][z.y + 1] = 0;
            }
        }

        if (z.x > 0) { // angle
            if (z.y > 0) {
                if (v[z.x - 1][z.y - 1] >= (*p) / 4) {
                    v[z.x - 1][z.y - 1] -= (*p) / 4;
                } else {
                    v[z.x - 1][z.y - 1] = 0;
                }
            }
            if (z.y < v[z.x - 1].size() - 1) {
                if (v[z.x - 1][z.y + 1] >= (*p) / 4) {
                    v[z.x - 1][z.y + 1] -= (*p) / 4;
                } else {
                    v[z.x - 1][z.y + 1] = 0;
                }
            }
        }

        if (z.x < (v.size() - 1)) { // angle
            if (z.y > 0) {
                if (v[z.x + 1][z.y - 1] >= (*p) / 4) {
                    v[z.x + 1][z.y - 1] -= (*p) / 4;
                } else {
                    v[z.x + 1][z.y - 1] = 0;
                }
            }
            if (z.y < v[z.x + 1].size() - 1) {
                if (v[z.x + 1][z.y + 1] >= (*p) / 4) {
                    v[z.x + 1][z.y + 1] -= (*p) / 4;
                } else {
                    v[z.x + 1][z.y + 1] = 0;
                }
            }
        }
    }
    for (unsigned  i = 0; i < v.size(); i++) {
        for (unsigned j = 0; j < v[i].size(); j++) {
            std::cout << v[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
