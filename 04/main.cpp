#include <iostream>
#include <limits>
#include <sstream>
#include <cassert>
#include <string>
#include "bigint.hpp"

using namespace std;


void BigNumberTest()
{
    string num1 = "14554548481512154185151524152415225220";
    string num2 = "78545465755632659595963232313059997944";
    string num3 = "14554548481512154185151524152415225221";
    string num4 = "78545465755632659595963232313059997943";

    BigInt N1(num1);
    BigInt N2(num2);
    BigInt N3;
    N3 = N1 + N2;
    assert(N3 == BigInt(num3) + BigInt(num4));
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
    assert(N1 == N2);
    assert(N4 == N3);
}

void CompareTest()
{
    string num1 = "78545465755632659595963232313059997944";
    string num2 = "78545465755632659595963232313059997945";

    BigInt N1 = 4321;
    BigInt N2 = 4320;
    BigInt N3(num1);
    BigInt N4(num2);

    assert(N1 > N2);
    assert(N4 > N3);
}

 

void ArithmeticTest()
{
    string num1 = "78545465755632659595963232313059997944";

    BigInt N1 = 4321;
    BigInt N2 = 4320;
    
    BigInt N3(num1);
    BigInt N4(num1);

    BigInt Zero = 0;

    BigInt N5;

    N5 = N1 + N2;

    assert(N1 > N2);
    assert(N4 == N3);
    assert(N1 != N3);
    assert(N5 == 4321 + 4320);
    assert(N3 == N4 * 1);
    assert(Zero == (N4 - N3));

}

void AroundZero()
{
    string num1 = "78545465755632659595963232313059997944";

    BigInt N1 = 4321;
    BigInt N2 = 4320;
    
    BigInt N3(num1);
    BigInt N4(num1);

    BigInt Zero = 0;

    BigInt N5;

    assert(Zero > N2 - N1);
    assert(Zero == N4 - N3);
    assert(Zero < N1 - N2);
}

int main()
{
    BigNumberTest();
    LogicalTest();
    MoveTest();
    ArithmeticTest();
    AroundZero();
    cout << "Success!\n";
    
    return 0;
}