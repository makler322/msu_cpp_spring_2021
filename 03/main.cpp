#include "matrix.hpp"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

void test()
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


int main()
{
	test();
	cout << "Success!\n";

	return 0;
}