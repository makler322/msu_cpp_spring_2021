#include <iostream>
#include <limits>
#include <sstream>
#include <cassert>
#include "bigint.hpp"

using namespace std;


void BigNumberTest()
{
    BigInt N1("14554548481512154185151524152415225220");
    BigInt N2("78545465755632659595963232313059997944");
    BigInt N3;
    N3 = N1 + N2;
    assert(N3 == BigInt("14554548481512154185151524152415225221") + BigInt("78545465755632659595963232313059997943"));
}

void LogicalTest()
{
    BigInt N1 = 4321;
    BigInt N2("4321");
    BigInt N3;
    
    assert(N1 == N2);
    assert(N1 != (-N2));
    assert(N1 >  N3);
    assert((-N1) <  N3);
    assert(N1 >= N2);
    assert(N1 <= (N2 + N1));
}

void MoveTest()
{
    BigInt N1 = 4321;
    BigInt N2;
    BigInt N3;
    N2 = N1;
    BigInt N4 = std::move(N1);
    N3 = std::move(N2);
    assert(N4 == N3);
}

int main()
{
    BigNumberTest();
    LogicalTest();
    MoveTest();
    cout << "Success!\n";
    
    return 0;
}