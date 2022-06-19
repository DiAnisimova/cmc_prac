class Sum
{
    int firstn, secondn;
    int sum;
public:
    Sum(int a, int b)
    {
        firstn = a;
        secondn = b;
        sum = a + b;
    }
    Sum(Sum obj, int c)
    {
        firstn = obj.get();
        secondn = c;
    }
    int get() const
    {
        return firstn + secondn;
    }
    ~Sum() {}
};
