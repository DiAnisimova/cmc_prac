class C
{
    int x;
public:
    C(int number = 0): x(0) {}
    C(int a, int b): x(a) {}
    C(const C &v): x(v.x) {}
    C & operator++()
    {
        x++;
        return *this;
    }
    friend int operator*(const C &v1, const C v2[])
    {
        return v1.x * v2->x;
    }
    friend int operator+(const C &v1, const C &v2)
    {
        return v1.x + v2.x;
    }
    friend int operator~(const C &v)
    {
        return -v.x;
    }
    operator int() { return 0; }
    C operator[] (int i) { return *this; }
    friend C operator&(const C &v)
    {
        return v;
    }
};
