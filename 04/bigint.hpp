#pragma once
#include <string>
#include <iostream>

using namespace std;


class BigInt
{
private:
    char *bigNum = nullptr;
    size_t size = 0;
    bool neg = false;
public:
    BigInt(int64_t num = 0);
    BigInt(std::string num);
    BigInt(const BigInt &Num);
    BigInt(BigInt &&Num);
    BigInt & operator = (const BigInt &Num);
    BigInt & operator = (BigInt &&Num);
    ~BigInt();
	
	BigInt operator + (const BigInt &Num) const;
    BigInt operator - () const;
    BigInt operator - (const BigInt &Num) const;
    void pow_10_n (const size_t n);
    BigInt operator * (const BigInt &Num) const;

    bool operator == (const BigInt &Num) const;
    bool operator != (const BigInt &Num) const;
    bool operator <  (const BigInt &Num) const;
    bool operator >  (const BigInt &Num) const;
    bool operator <= (const BigInt &Num) const;
    bool operator >= (const BigInt &Num) const;
    
    friend std::ostream & operator << (std::ostream &ostream, const BigInt &Num);
};