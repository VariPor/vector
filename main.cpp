#include "vector.h"
#include <iostream>
#include <string>

template <class T>
void print(vector<T> &v)
{
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

    std::cout << "v1: ";
    print(v1);
    std::cout << "v2: ";
    print(v2);
    std::cout << "v3: ";
    print(v3);
    std::cout << "v4: ";
    print(v4);
    std::cout << "v5: ";
    print(v5);
    std::cout << "v6: ";
    print(v6);
    std::cout << "v7: ";
    print(v7);
    std::cout << "v8: ";
    print(v8);
    std::cout << "v9: ";
    print(v9);
    std::cout << "v10: ";
    print(v10);
    std::cout << "v11: ";
    print(v11);
    std::cout << "v12: ";
    print(v12);
    std::cout << "v13: ";
    print(v13);
    std::cout << "v14: ";
    print(v14);
    std::cout << "v15: ";
    print(v15);
    std::cout << "v16: ";
    print(v16);
    std::cout << "v17: ";
    print(v17);
    std::cout << "v18: ";
    print(v18);
    std::cout << "v19: ";
    print(v19);

    v1 = v2;
    v2 = vector<int> {4};

    std::cout << "v1, v2:\n"; 
    print(v1);
    print(v2);

    std::cout << '\n';
    vector<int> g(12, 12);
    vector<int> c = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << "g: ";
    print(g);
    g.push_back(5);
    std::cout << "space: " << g.capacity() << '\n';
    std::cout << "g, c:\n";
    print(g);
    print(c);

    vector<test> empty;
    vector<int> empty1(0);

    std::cout << "empty, empty1:\n"; 
    print(empty);
    print(empty1);

    vector<int> copy(v9);
    vector<std::string> copy1(v6);
    vector<test> copy2(v18);

    std::cout << "copy, copy1, copy2:\n"; 
    print(copy);
    print(copy1);
    print(copy2);

    std::cout << copy1.at(1) << '\n';  
    //std::cout << copy1.at(2);

    std::cout << copy1[1] << '\n';  
    std::cout << v13[2] << '\n';
    //std::cout << v13[5] << '\n';

    vector<std::string> s1{"123", "ert", "tyu"};
    //std::cout << "s1:\n";
    //print(s1);

    s1.push_back("56293");
    std::cout << "s1:\n";
    print(s1);


    return 0;
}
