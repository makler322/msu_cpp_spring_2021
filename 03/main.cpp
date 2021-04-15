#include "matrix.hpp"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

void SimpleTest()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    assert(m.getRows() == 5);
    assert(m.getCols() == 3);
    m[1][2] = 5; // строка 1, колонка 2

    double x = m[4][1];
    assert(x == 0);
    m *= 3; // умножение на число
    Matrix m1(rows, cols);

    Matrix m2 = m1 + m;
    std::cout << m2 << std::endl;
}

void CompareTest()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m1(rows, cols);
    Matrix m2(rows, cols);
    assert(m1 == m2);
    m1[1][2] = 5;
    assert(m1 != m2);
}

void Matrix1x1Test()
{
    const size_t rows = 1;
    const size_t cols = 1;

    Matrix m1(rows, cols);
    Matrix m2(rows, cols);
    assert(m1 == m2);
    m1[0][0] = 5;
    assert(m1 != m2);
    m2 = m1 + m2;
    assert(m1 == m2);
}

void ChangeFullMatrixTest()
{
    const size_t rows = 3;
    const size_t cols = 4;

    Matrix m(rows, cols);
    m[1][1] = 1; 
    m[1][2] = 2;
    m[1][3] = 3;

    m[0][1] = 4; 
    m[0][2] = 5;
    m[0][3] = 6;

    std::cout << m << std::endl;
    assert(m[1][2] == 2);
    assert(m[0][2] == 5);

}

void Compare2DifferentMatrixTest()
{
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m1(rows, cols);
    Matrix m2(cols, rows);
    assert(m1 != m2);
}

void GetSizeMatrixTest()
{
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix m(rows, cols);
    
    assert(m.getRows() == 5);
    assert(m.getCols() == 3);
}

void OutOfRangeTest()
{
    const size_t rows = 5;
    const size_t cols = 3;
    bool my_try = false;
    Matrix m(rows, cols);
    try 
    {
        m[0][10] = 5;
    }
    catch (...)
    {
        my_try = true;
    }
    assert(my_try);
    my_try = false;
    try 
    {
        m[10][0] = 5;
    }
    catch (...)
    {
        my_try = true;
    }
    assert(my_try);
}

int main()
{
    SimpleTest();
    CompareTest();
    Matrix1x1Test();
    ChangeFullMatrixTest();
    Compare2DifferentMatrixTest();
    GetSizeMatrixTest();
    OutOfRangeTest();
    cout << "Success!\n";

    return 0;
}