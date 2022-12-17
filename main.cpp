#include "vector.h"
#include <iostream>
#include <string>

template <class T>
void print(vector<T> &v, std::string s)
{
    std::cout << s << '\n';
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}

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


int main()
{
    vector<int> v1{1, 2};
    vector<int> v2(5);
    vector<int> v9(3, 9);
    vector <double> v3(3);
    vector <double> v4{6.9};
    vector<double> v10(3, 9.9);
    vector <std::string> v5{};
    vector <std::string> v6{" stghnu", "gf"};
    vector<std::string> v11(3, "flag");
    vector <bool> v7{true, false, true};
    vector <bool> v8(3);
    vector<bool> v12(3, true);
    vector <char> v13{'w', '7', '9'};
    vector <char> v14(3);
    vector<char> v15(3, '*');  
    vector<std::string> v16{3, "a"}; 
    vector <test> v17(3);
    test t{3, 'l', false};
    vector<test> v18{3, t};  
    vector<test> v19{t};

    print(v1, "v1");
    v1.push_back(30);
    print(v1, "v1");
    print(v2, "v2");
    print(v3, "v3");
    print(v4, "v4");
    print(v5, "v5");
    print(v6, "v6");
    print(v7, "v7");
    print(v8, "v8");
    print(v9, "v9");
    print(v10, "v10");
    print(v11, "v11");
    print(v12, "v12");
    print(v13, "v13");
    print(v14, "v14");
    print(v15, "v15");
    print(v16, "v16");
    print(v17, "v17");
    print(v18, "v18");
    print(v19, "v19");

    v1 = v2;
    v2 = vector<int> {4};
 
    print(v1, "v1");
    print(v2, "v2");

    std::cout << '\n';
    vector<int> v20(12, 12);
    vector<int> v21 = {1, 2, 3, 4, 5, 6, 7, 8};
    print(v20, "v20");
    v20.push_back(5);
    std::cout << "space: " << v20.capacity() << '\n';
    print(v20, "v20");
    print(v21, "v21");

    vector<test> empty;
    vector<int> empty1(0);

    print(empty, "empty");
    print(empty1, "empty1");

    vector<int> copy(v9);
    vector<std::string> copy1(v6);
    vector<test> copy2(v18);
 
    print(copy, "copy");
    print(copy1, "copy1");
    print(copy2, "copy2");

    std::cout << "copy1.at(1) " << copy1.at(1) << '\n';  

    std::cout << "copy1[1] " << copy1[1] << '\n';  
    std::cout << "v13[2] " << v13[2] << '\n';

    vector<vector<int>> vv{{1, 2, 3}};
    for (int i = 0; i < vv.size(); ++i)
        print(vv[i], " ");

    return 0;
}
