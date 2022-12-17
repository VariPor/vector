#include <initializer_list>
#include <algorithm>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <class T, class A = std::allocator<T>>
struct vector_base
{
    A alloc;
    int sz;
    T *elem;
    int space;

    vector_base(int n)
        : elem{alloc.allocate(n)}, sz{n}, space{n} {}
    vector_base()
        : elem{nullptr}, sz{0}, space{0} {}
    ~vector_base() { alloc.deallocate(elem, space); }
};

template <class T, class A = std::allocator<T>>
class vector : private vector_base<T>
{
public:
    vector()
        : vector_base<T>() {}

    explicit vector(int s, T val = T{})
        : vector_base<T>(s)
    {
        for (int i = 0; i < s; ++i)
            this->alloc.construct(&this->elem[i], val);
    }

    vector(const vector &);
    vector<T, A> &operator=(const vector &);

    vector(vector &&a);
    vector &operator=(vector &&);

    T &at(int n);
    const T &at(int n) const;

    const T &operator[](int n) const
    {
        return this->elem[n];
    }

    T &operator[](int n)
    {
        return (this->elem[n]);
    }

    vector(std::initializer_list<T> lst)
        : vector_base<T>(lst.size())
    {
        for (int i = 0; i < lst.size(); ++i)
            this->alloc.construct(this->elem+i, *(lst.begin() + i));
    }

    ~vector()
    {
        for (int i = 0; i < this->sz; ++i)
            this->alloc.destroy(this->elem + i);
    }
    int size() const { return this->sz; }

    /*T get(int n) const { return (this->elem)[n]; }
    void set(int n, T v) { (this->elem)[n] = v; }*/

    void reserve(int newalloc);
    int capacity() const;
    void resize(int newsize, T val = T());

    void push_back(const T &d);
};

template <class T, class A>
vector<T, A>::vector(const vector &arg)
    : vector_base<T, A>(arg.sz)
{
    for (int i = 0; i < arg.size(); ++i)
        this->alloc.construct(this->elem + i, arg.elem[i]);
}

template <class T, class A>
vector<T, A>::vector(vector &&a)
{
    std::cout << "success\n";
    this->sz = a.sz;
    this->elem = a.elem;
    this->space = a.sz;
    a.sz = 0;
    a.elem = nullptr;
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(vector &&a)
{
    std::cout << "success\n";
    for (int i = 0; i < this->sz; ++i)
        this->alloc.destroy(this->elem + i);
    this->alloc.deallocate(this->elem, this->space);
    this->elem = a.elem;
    this->sz = a.sz;
    this->space = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

template <class T, class A>
void vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= this->space)
        return;
    T *p = this->alloc.allocate(newalloc);
    for (int i = 0; i < this->sz; ++i)
        this->alloc.construct(&p[i], (this->elem)[i]);

    for (int i = 0; i < this->sz; ++i)
        this->alloc.destroy(this->elem + i);

    this->alloc.deallocate(this->elem, this->space);
    this->elem = p;
    this->space = newalloc;
}

template <class T, class A>
int vector<T, A>::capacity() const { return this->space; }

template <class T, class A>
void vector<T, A>::resize(int newsize, T val)
{
    if (newsize < this->sz)
        throw std::runtime_error("resize: newsize < size");
    reserve(newsize);
    for (int i = this->sz; i < newsize; ++i)
        this->alloc.construct(this->elem + i, val);
    for (int i = newsize; i < this->sz; ++i)
        this->alloc.destroy(this->elem + i);
    this->sz = newsize;
}

template <class T, class A>
void vector<T, A>::push_back(const T &val)
{
    if (this->space == 0)
        reserve(8);
    else if (this->sz == this->space)
        reserve(2 * this->space);
    this->alloc.construct(this->elem +this->sz, val);
    ++(this->sz);
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(const vector &a)
{
    if (this == &a)
        return *this;

    if (a.sz <= this->space)
    {
        for (int i = 0; i < this->sz; ++i)
            this->alloc.destroy(this->elem + i);
        for (int i = 0; i < a.sz; ++i)
            this->alloc.construct(this->elem + i, a.elem[i]);
        this->sz = a.sz;
        return *this;
    }

    T *p = this->alloc.allocate(a.sz);

    for (int i = 0; i < a.sz; ++i)
        this->alloc.construct(&p[i], a.elem[i]);

    for (int i = 0; i < this->sz; ++i)
        this->alloc.destroy(this->elem + i);

    this->alloc.deallocate(this->elem, this->space);
    this->space = this->sz = a.sz;
    this->elem = p;
    return *this;
}

template <class T, class A>
T &vector<T, A>::at(int n)
{
    if (n < 0 || this->sz <= n)
        throw std::out_of_range("out of range");
    return (this->elem)[n];
}

template <class T, class A>
const T &vector<T, A>::at(int n) const
{
    if (n < 0 || this->sz <= n)
        throw std::out_of_range("out of range");
    return (this->elem)[n];
}