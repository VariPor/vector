#include <initializer_list>
#include <algorithm>
#include <memory>
#include <algorithm>
#include <stdexcept>

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

    explicit vector(int s, T val = T{});

    vector(const vector &);
    vector<T, A> &operator=(const vector &);

    vector(vector &&a);
    vector &operator=(vector &&);

    T &at(int n);
    const T &at(int n) const;

    const T &operator[](int n) const
            { return this->elem[n]; }

    T &operator[](int n)
        { return (this->elem[n]); }

    vector(std::initializer_list<T> lst);   

    ~vector()
    {
        for (int i = 0; i < this->sz; ++i)
            this->alloc.destroy(this->elem + i);
    }

    int size() const { return this->sz; }

    void reserve(int newalloc);
    int capacity() const;
    void resize(int newsize, T val = T());

    void push_back(const T &d);
};

template <class T, class A>
vector<T, A>::vector(const vector &arg)
    try
    : vector_base<T, A>(arg.sz)
        {
            for (int i = 0; i < arg.size(); ++i)
            {
                this->sz = i + 1;
                this->alloc.construct(this->elem + i, arg.elem[i]);
            }
        }
    catch (std::exception& e) 
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw e; }
    catch (...) 
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw "unknown exception"; 
    }

template <class T, class A>
vector<T, A>::vector(vector &&a)
{
    this->sz = a.sz;
    this->elem = a.elem;
    this->space = a.sz;
    a.sz = 0;
    a.space = 0;
    a.elem = nullptr;
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(vector &&a)
    {
        for (int i = 0; i < this->sz; ++i)
            this->alloc.destroy(this->elem + i);
        this->alloc.deallocate(this->elem, this->space);
        this->elem = a.elem;
        this->sz = a.sz;
        this->space = a.sz;
        a.elem = nullptr;
        a.space = 0;
        a.sz = 0;
        return *this;
    }

template <class T, class A>
void vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= this->space)
            return;
        T *p = this->alloc.allocate(newalloc);
        int init = 0;
    try
    {
        for (int i = 0; i < this->sz; ++i)
        {
            init = i + 1;
            this->alloc.construct(&p[i], this->elem[i]);
        }

        for (int i = 0; i < init; ++i)
            this->alloc.destroy(this->elem + i);

        this->alloc.deallocate(this->elem, this->space);
        this->elem = p;
        this->space = newalloc;
    }

    catch (std::exception& e) 
    { 
        for (int j = 0; j < init; ++j)
            this->alloc.destroy(&p[j]);
        this->alloc.deallocate(p, this->sz);
        throw e; 
    }
    catch (...) 
    { 
        for (int j = 0; j < init; ++j)
            this->alloc.destroy(&p[j]);
        this->alloc.deallocate(p, this->sz);
        throw "unknown exception"; 
    }
}

template <class T, class A>
int vector<T, A>::capacity() const { return this->space; }

template <class T, class A>
void vector<T, A>::resize(int newsize, T val)
    try
    {
        if (newsize < this->sz)
            throw std::runtime_error("resize: newsize < size");
        reserve(newsize);
        int init = this->sz;
        for (int i = init; i < newsize; ++i)
        {
            this->sz = i + 1;
            this->alloc.construct(this->elem + i, val);
        }
        for (int i = newsize; i < init; ++i)
            this->alloc.destroy(this->elem + i);
        this->sz = newsize;
    }
    catch (std::exception& e) 
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw e; 
    }
    catch (...) 
    {
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw "unknown exception"; 
    }

template <class T, class A>
void vector<T, A>::push_back(const T &val)
{
    try
    {
        if (this->space == 0)
            reserve(8);
        else if (this->sz == this->space)
            reserve(2 * this->space);
        this->alloc.construct(this->elem +this->sz, val);
        ++(this->sz);
    }
    catch (std::exception& e) 
    {
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw e; 
    }
    catch (...) 
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw "unknown exception"; 
    }
}

template <class T, class A>
vector<T, A> &vector<T, A>::operator=(const vector &a)
    {
        if (this == &a)
            return *this;

        if (a.sz <= this->space)
        try
        {
            for (int i = 0; i < this->sz; ++i)
                this->alloc.destroy(this->elem + i);
            for (int i = 0; i < a.sz; ++i)
            {
                this->sz = i + 1;
                this->alloc.construct(this->elem + i, a.elem[i]);
            }
            this->sz = a.sz;
            return *this;
        }
        catch (std::exception& e) 
        { 
            for (int j = 0; j < this->sz; ++j)
                this->alloc.destroy(&this->elem[j]);
            this->sz = 0;
            throw e; 
        }
        catch (...) 
        { 
            for (int j = 0; j < this->sz; ++j)
                this->alloc.destroy(&this->elem[j]);
            this->sz = 0;
            throw "unknown exception"; 
        }

        T *p = this->alloc.allocate(a.sz);
        int init = 0;

        try
        {
            for (int i = 0; i < a.sz; ++i)
            {
                init = i + 1;
                this->alloc.construct(&p[i], a.elem[i]);
            }
        }
        catch (std::exception& e) 
        { 
            for (int j = 0; j < init; ++j)
                this->alloc.destroy(&p[j]);
            this->alloc.deallocate(p, init);
            throw e; 
        }
        catch (...) 
        { 
            for (int j = 0; j < init; ++j)
                this->alloc.destroy(&p[j]);
            this->alloc.deallocate(p, init);
            throw "unknown exception"; 
        }

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

template <class T, class A>
vector<T, A>::vector(std::initializer_list<T> lst)
    try
        : vector_base<T>(lst.size())
        {
            for (int i = 0; i < lst.size(); ++i)
            {
                this->sz = i + 1;
                this->alloc.construct(this->elem+i, *(lst.begin() + i));
            }
        }
    catch (std::exception& e)
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw; 
    }
    catch (...) 
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        this->sz = 0;
        throw; 
    } 

template <class T, class A>
vector<T, A>::vector(int s, T val)
    try
        : vector_base<T>(s)
        {
            for (int i = 0; i < s; ++i)
            {
                this->alloc.construct(&this->elem[i], val);
                this->sz = i + 1;
            }
        }
    catch (std::exception& e)
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        throw; 
    }
    catch (...) 
    { 
        for (int j = 0; j < this->sz; ++j)
            this->alloc.destroy(&this->elem[j]);
        throw; 
    };