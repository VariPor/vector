#include <initializer_list>
#include <algorithm>
#include <memory>


template<class T, class A>
struct vector_base
{
    A alloc;
    int sz;
    T* elem;
    int space;

    vector_base(const A& a, int n)
        :alloc{a}, elem{a.allocate(n)}, sz{n}, space{n}{}
    vector_base(int n, const A& a)
        :alloc{a}, elem{a.allocate(n)}, sz{n}, space{n}{}
    vector_base()
        : elem{nullptr}, sz{0}, space{0}
        {}
    //vector_base() = default;
    ~vector_base() { alloc.deallocate(elem, space); }
};

template<class T, class A = std::allocator<T>> 
class vector : private vector_base<T, A>
{
    A alloc;
    int sz;
    T* elem;
    int space;
public:
    vector(): sz{0}, elem{nullptr}, space{0} {}

    explicit vector(int s)
    :sz{s}, elem{new T[s]}, space{s}
    {
        for (int i = 0; i < s; ++i)
            elem[i] = 0;
    }

    vector (const vector&);
    vector& operator=(const vector&);

    vector(vector&& a);
    vector& operator=(vector&&);

    T& at(int n);
    const T& at(int n) const;

    const T& operator[](int n) const
        { return elem[n]; }
    T& operator[](int n)
        { return (elem[n]); }

    vector(std::initializer_list<T> lst)
        :sz{lst.size()}, elem {new T[sz]}
    {
        std::copy(lst.begin(), lst.end(), elem);
    }
    ~vector() { delete[] elem; }
    int size () const { return sz; }

    T get(int n) const { return elem[n]; }
    void set(int n, T v) { elem[n] = v; }

    void reserve(int newalloc);
    int capacity() const;
    void resize(int newsize, T val = T());

    void push_back(const T& d);
};

