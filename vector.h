#include <initializer_list>
#include <algorithm>
#include <memory>
#include <algorithm>
#include <stdexcept>

template <class T, class A>
struct vector_base
{
    A alloc;
    int sz;
    T *elem;
    int space;

    vector_base(const A &a, int n)
        : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{0} {}
    vector_base()
        : elem{nullptr}, sz{0}, space{0} {}
    ~vector_base() { alloc.deallocate(elem, space); }
};

template <class T, class A = std::allocator<T>>
// class vector : private vector_base<T, A>
class vector
{
    A alloc;
    int sz;
    T *elem;
    int space;

public:
    vector() : sz{0}, elem{alloc.allocate(0)}, space{0} {}

    explicit vector(int s, T val = T{})
        : sz{s}, elem{alloc.allocate(s)}, space{s}
    {
        for (int i = 0; i < s; ++i)
            alloc.construct(&elem[i], val);
    }

    vector(const vector &);
    vector<T, A> &operator=(const vector &);

    vector(vector &&a);
    vector &operator=(vector &&);

    T &at(int n);
    const T &at(int n) const;

    const T &operator[](int n) const
    {
        return elem[n];
    }

    T &operator[](int n)
    {
        return (elem[n]);
    }

    vector(std::initializer_list<T> lst)
        : sz{lst.size()}, elem{alloc.allocate(lst.size())}, space{lst.size()}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }
    ~vector()
    {
        for (int i = 0; i < sz; ++i)
            alloc.destroy(this + i);
        alloc.deallocate(elem, space);
    }
    int size() const { return sz; }

    T get(int n) const { return elem[n]; }
    void set(int n, T v) { elem[n] = v; }

    void reserve(int newalloc);
    int capacity() const;
    void resize(int newsize, T val = T());

    void push_back(const T &d);
};

template <class T, class A>
vector<T, A>::vector(const vector &arg)
    : sz{arg.sz}, elem{alloc.allocate(arg.sz)}, space{arg.sz}
{
    std::copy(arg.elem, arg.elem + arg.sz, elem);
}

template <class T, class A>
vector<T, A>::vector(vector &&a)
    : sz{a.sz}, elem{a.elem}, space{a.sz}
{
    a.sz = 0;
    a.elem = nullptr;
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(vector &&a)
{
    //delete[] elem;
    for (int i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem, space);
    elem = a.elem;
    sz = a.sz;
    space = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

template <class T, class A>
void vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= space)
        return;
    T *p = alloc.allocate(newalloc);
    for (int i = 0; i < sz; ++i)
        alloc.construct(&p[i], elem[i]);

    for (int i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);

    alloc.deallocate(elem, space);
    elem = p;
    space = newalloc;
}

template <class T, class A>
int vector<T, A>::capacity() const { return space; }

template <class T, class A>
void vector<T, A>::resize(int newsize, T val)
{
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        alloc.construct(&elem[i], val);
    for (int i = newsize; i < sz; ++i)
        alloc.destroy(&elem[i]);
    sz = newsize;
}

template <class T, class A>
void vector<T, A>::push_back(const T &val)
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2 * space);
    elem[sz] = val;
    ++sz;
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(const vector &a)
{
    if (this == &a)
        return *this;

    if (a.sz <= space)
    {
        for (int i = 0; i < a.sz; ++i)
            elem[i] = a.elem[i];
        sz = a.sz;
        return *this;
    }

    T *p = alloc.allocate(a.sz);

    for (int i = 0; i < a.sz; ++i)
        p[i] = a.elem[i];

    for (int i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);
        
    alloc.deallocate(elem, space);
    space = sz = a.sz;
    elem = p;
    return *this;
}

template <class T, class A>
T &vector<T, A>::at(int n)
{
    if (n < 0 || sz <= n)
        throw std::out_of_range("out of range");
    return elem[n];
}

template <class T, class A>
const T &vector<T, A>::at(int n) const
{
    if (n < 0 || sz <= n)
        throw std::out_of_range("out of range");
    return elem[n];
}

// #include <vector>
// std::vector<int>