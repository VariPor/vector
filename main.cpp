#include "vector.h"
#include <iostream>
#include <string>

template <class T>
void print(vector<T> v)
{
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
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
    
    print(v1);
    print(v2);
    print(v3);
    print(v4);
    print(v5);
    print(v6);
    print(v7);
    print(v8);
    print(v9);
    print(v10);
    print(v11);
    print(v12);
    print(v13);
    print(v14);
    print(v15);
    print(v16);
    return 0;
}

#include <vector>

//std::vector<int> v;