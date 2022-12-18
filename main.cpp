#include "vector.h"
#include "classes.h"
#include <string>

template <class T>
void print(const vector<T> &v, std::string s)
{
    std::cout << s << ":\n";
    for (int i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << "\n\n";
}
template <class T>
void print_vector(vector<vector<T>> &v, std::string s)
{
    std::cout << s << ":\n";
    for (int i = 0; i < v.size(); ++i)
        for (int j = 0; j < v[i].size(); ++j)
        {
            //std::cout << v[i].size() << '\n';
            std::cout << "i = " << i << ", j = " << j << "; value: " << v[i][j] << '\n';
        }
    std::cout << "\n\n";
}

template<class T>
T f (T a)
{
    return a;
}

int main()
try
{
    /*vector<int> v1{1, 2};
    print(v1, "v1");
    v1.push_back(30);
    print(v1, "v1");

    vector<int> v2(5);
    print(v2, "v2");

    vector <double> v3(3);
    print(v3, "v3");

    vector <double> v4{6.9};
    print(v4, "v4");

    vector <std::string> v5{};
    print(v5, "v5");

    vector <std::string> v6{" stghnu", "gf"};
    print(v6, "v6");

    vector <bool> v7{true, false, true};
    print(v7, "v7");

    vector <bool> v8(3);
    print(v8, "v8");

    vector<int> v9(3, 9);
    print(v9, "v9");

    vector<double> v10(3, 9.9);
    print(v10, "v10");

    vector<std::string> v11(3, "flag");
    print(v11, "v11");

    vector<bool> v12(3, true);
    print(v12, "v12");

    vector <char> v13{'w', '7', '9'};
    print(v13, "v13");

    vector <char> v14(3);
    print(v14, "v14");

    vector<char> v15(3, '*');
    print(v15, "v15");

    vector<std::string> v16{3, "a"}; 
    print(v16, "v16");

    vector <test> v17(3);
    print(v17, "v17");

    test t{3, 'l', false};
    vector<test> v18{3, t};
    print(v18, "v18");

    vector<test> v19{t};
    print(v19, "v19");


    v1 = v2;
    v2 = vector<int> {4};
 
    print(v1, "v1");
    print(v2, "v2");

    vector<int> v20(12, 12);
    print(v20, "v20");
    v20.push_back(5);
    std::cout << "space: " << v20.capacity() << '\n';
    print(v20, "v20");

    vector<int> v21 = {1, 2, 3, 4, 5, 6, 7, 8};
    print(v21, "v21");

    vector<test> empty;
    print(empty, "empty");

    vector<int> empty1(0); 
    print(empty1, "empty1");

    vector<int> copy(v9);
    print(copy, "copy");

    vector<std::string> copy1(v6);
    print(copy1, "copy1");
    
    vector<test> copy2(v18);   
    print(copy2, "copy2");

    std::cout << "copy1.at(1): " << copy1.at(1) << '\n';  

    std::cout << "copy1[1]: " << copy1[1] << '\n';  
    std::cout << "v13[2]: " << v13[2] << '\n';

    vector<vector<int>> vv{v1, v1};
    vv[0].push_back(1);
    vv.push_back(vector<int> {1, 2, 3});
    print_vector(vv, "vv");

    vector<std::string> vs{"a", "b", "c"};
    print(vs, "vs");
    vs.push_back("tyyt");
    print(vs, "vs");

    vector<double> vd{2.3, 5.4};
    print(vd, "vd");
    vd.push_back(5.5);
    print(vd, "vd");
    
    vector<int> vi{2, 5, 4};
    print(vi, "vd");
    vi.push_back(58);
    print(vi, "vi");

    vector<char> vc{'r', 'l', 'p'};
    print(vc, "vc");
    vc.push_back('u');
    print(vc, "vc");

    test tt{6, '8', true};
    vector<test> vt{t, tt, t};
    print(vt, "vt");
    vt.push_back(tt);
    print(vt, "vt");

    vector<std::string> s1{"print", "this", "vector", "please"};
    print(s1, "s1");

    vector<std::string> s2{"and", "this", "too"};
    print(s2, "s2");

    s1 = s2;
    print(s1, "s1");
    print(s2, "s2");

    s1.push_back("ttttttttttttttttttttttttttttttt");
    print(s1, "s1");

    s1 = f(vector<std::string> {"67", "76"});
    print(s1, "s1");

    vector<std::string> s3 = f(vector<std::string> {"57", "88"});
    print(s3, "s3");

    s3[1] = "99";
    print(s3, "s3[1] = \"99\"");

    vector<vector<int>> vv1{v1};
    print_vector(vv1, "vv1");

    vector<vector<int>> vv2{vi};
    print_vector(vv2, "vv2");

    vv1 = vv2;
    print_vector(vv1, "vv1");
    print_vector(vv2, "vv2");

    const vector<int> cvi{1, 2, 3};
    print(cvi, "cvi");

    std::cout << cvi[1] << " - cvi[1]\n\n";

    vector<int> vii;
    vii.push_back(1);
    print(vii, "vii");


    vector<std::string> a(10, "777");
    vector <std::string> b (5, "5");
    b = a;
    print(a, "a");*/

    ExceptTest et1{4, '8', true};
    ExceptTest et2{8, '7', false};
    ExceptTest et3{7, 't', true};

    std::cout << et1 << '\n' << et2 << '\n' << et3 << '\n';

    //vector<ExceptTest> et{et1, et2, et3, {-7, 't', true}};
    //print(et, "et");

    //vector<ExceptTest> ett(2, {-7, 't', true});
    //print(ett, "ett");

    vector<ExceptTest> ettt{et1};
    print(ettt, "ettt");



    return 0;
}
catch (std::exception& e)
{
  std::cerr << "exception: " << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "unknown exception" << std::endl;
  return 2;
}