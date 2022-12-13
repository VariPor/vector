#include "vector.h"
#include <algorithm>
#include <stdexcept>

template<class T, class A>
vector<T, A>::vector(const vector& arg)
    :sz{arg.sz}, elem(new T[arg.sz])
{
    std::copy(arg.elem, arg.elem + arg.sz, elem);
}


/*vector& vector::operator=(const vector& a)
{
    T* p = new T[a.sz];
    std::copy(a.elem, a.elem + a.sz, p);
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}*/

template<class T, class A>
vector<T, A>::vector(vector&& a)
    :sz{a.sz}, elem{a.elem}
    {
        a.sz = 0;
        a.elem = nullptr;
    }

template<class T, class A>
vector<T, A>& vector<T, A>::operator=(vector&& a)
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

template<class T, class A>
void vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= this->space) return;
    vector_base<T, A> b(this->alloc, newalloc);
    std::uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);
    T* p = alloc.allocate(newalloc);

    for (int i = 0; i < this->sz; ++i) 
        alloc.destroy(&this->elem[i]);
    std::swap<vector_base<T, A>>(*this, b);
}

template<class T, class A>
int vector<T, A>::capacity() const { return space; }

template<class T, class A>
void vector<T, A>::resize(int newsize, T val)
{
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        alloc.construct(&elem[i], val);
    for (int i = newsize; i < sz; ++i)
        alloc.destroy(&elem[i]);
    sz = newsize;
}

template<class T, class A>
void vector<T, A>::push_back(const T& val)
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2 * space);
    alloc.construct(&elem[sz], val);
    ++sz;
}

template<class T, class A>
vector<T, A>& vector<T, A>::operator=(const vector& a)
{
    if (this == &a) return *this;

    if (a.sz <= space)
    {
        for (int i = 0; i < a.sz; ++i)
            elem[i] = a.elem[i];
        sz = a.sz;
        return *this;
    }
    T* p = new T[a.sz];
    for (int i = 0; i < a.sz; ++i)
        p[i] = a.elem[i];
    delete[] elem;
    space = sz = a.sz;
    elem = p;
    return *this;
}


template<class T, class A>
T& vector<T, A>::at(int n)
{
    if (n < 0 || sz <= n) throw std::out_of_range();
    return elem[n];
}

template<class T, class A>
const T& vector<T, A>::at(int n) const
{
    if (n < 0 || sz <= n) throw std::out_of_range();
    return elem[n];
}