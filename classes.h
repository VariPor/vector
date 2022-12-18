#include <iostream>

struct test
{
    int x;
    char c;
    bool b;
    test() : x{0}, c{'a'}, b{true} {}
    test(int xx, char cc, bool bb) : x{xx}, c{cc}, b{bb} {}
    ~test() = default;
};

std::ostream& operator<<(std::ostream& os, const test&t)
{
    return os << t.x << ' ' << t.c << ' ' << t.b;
}

struct ExceptTest
{
    int* x;
    char c;
    bool b;
    ExceptTest() : x{nullptr}, c{'a'}, b{true} {}
    ExceptTest(int xx, char cc, bool bb) 
        : c{cc}, b{bb}
        {
            if (xx < 0) throw std::runtime_error("xx < 0\n");
            x = new int (xx);
        }

    ExceptTest(const ExceptTest &arg)
    : c{arg.c}, b{arg.b}
    {
        x = new int(*arg.x);
    }

    ~ExceptTest() 
    {
        if (x != nullptr)
            delete x;
    }

    ExceptTest(ExceptTest &&a)
    :c{a.c}, b{a.b}
    {
        x = a.x;;
        a.x = nullptr;
    }
    
    ExceptTest operator=(ExceptTest &&a)
    {
    delete x;
    c = a.c;
    b = a.c;
    x = a.x;
    a.x = nullptr;
    return *this;
    }
    
    ExceptTest operator=(const ExceptTest &a)
    {
        if (this == &a)
            return *this;
        b = a.b;
        c = a.c;
        x = new int (*a.x);
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, const ExceptTest&t)
{
    return os << *(t.x) << ' ' << t.c << ' ' << t.b;
}