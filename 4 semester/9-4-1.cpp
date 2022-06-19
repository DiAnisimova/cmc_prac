int main()
{
    int count;
    std::cin >> count;
    Holder *buf = new Holder[count];
    for (auto i = 0; i < count / 2; i++) {
        buf[i].swap(buf[count - 1 - i]);
    }
    delete []buf;
    return 0;
}
