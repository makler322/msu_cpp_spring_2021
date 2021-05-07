#include "vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void CorrectTest()
{
    Vector<int> v0;
    Vector<int> v1(3);
    Vector<int> v2(4, 1);
    Vector<int> v3 = {1, 2, 3};
    Vector<int> v4 = v3;
    Vector<int> v5 = std::move(v4);
    
    assert(v0.empty() == true);
    
    v1.pop_back();
    assert(v1.size() == 2);
    
    assert(v2.capacity() == 8);
    v2.reserve(10);
    assert(v2.capacity() == 10);
    
    v3.clear();
    assert(v3.empty() == true);
    
    v5.emplace_back(1, 2, 3);
    v5.push_back(4);
    assert(v5.size() == 7);
    v5.resize(10);
    assert(v5.size() == 10);
}


void ElemValueTest()
{
    Vector<int> v0 = {1, 2, 3};
    Vector<int> v1 = v0;
    std::string str;
    
    v0.emplace_back(4, 5, 6);
    v1.push_back(0);
    
    try
    {
        v0[10];
    }
    catch (std::out_of_range &err)
    {
        str = err.what();
    }
    assert(str == "Wrong index");
    
    assert(v0[5] == 6);
    assert(v1[0] == 1);
    assert(v1[3] == 0);
}


void IteratorTest()
{
    Vector<int> v = {0, 1, 2};
    
    Iterator<Vector<int>::iterator> i1 = v.begin();
    Iterator<Vector<int>::iterator> i2 = v.rbegin();
    Iterator<Vector<int>::iterator> i3 = v.end();
    Iterator<Vector<int>::iterator> i4 = v.rend();
    
    ++i1;
    ++i2;
    assert(i1 == i2);
    
    ++i1;
    ++i1;
    assert(i1 == i3);
    
    ++i2;
    ++i2;
    assert(i2 == i4);
}

void TypeTest()
{
    Vector<std::string> v0 = {"A", "B", "C"};
    Vector<std::vector<char>> v1 = {{'a', 'b'}, {'c'}};
    
    v0.resize(5);
    assert(v0[4] == "");
    
    v0.resize(7, "D");
    assert(v0[4] == "");
    assert(v0[5] == "D");
    
    
    v1.resize(3);
    std::vector<char> v = {};
    assert(v1[2] == v);
    
    v = {'d', 'e'};
    v1.resize(5, v);
    assert(v1[4] == v);
}


int main()
{
    CorrectTest();
    ElemValueTest();
    IteratorTest();
    TypeTest();
    
    cout << "Success!\n";
    
    return 0;
}