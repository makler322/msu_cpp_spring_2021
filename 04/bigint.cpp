#include <iostream>
#include "bigint.hpp"
#include <string>
#include <string.h>
#include <stdlib.h>

BigInt :: BigInt(int64_t num)
{

    std::string strNum = to_string(num);
    if (strNum[0] == '-')
    {
        neg = true;
        strNum.erase(0,1);
    }
    size = strNum.length();
    bigNum = new char [size];
    for (size_t i = 0; i < size; i++)
    {
        bigNum[i] = strNum[size - 1 - i];
    }
}

BigInt :: BigInt(std::string strNum)
{
    if (strNum[0] == '-')
    {
        neg = true;
        strNum.erase(0,1);
    }
    bool flag = true;
    for (size_t i = 0; i < strNum.length(); i++)
    {
        flag = flag & isdigit(strNum[i]);
    }
    if (!flag)
    {
        throw "String is not a number";
    }
    while ((strNum[0] == '0') && (strNum.length() != 1))
    {
        strNum.erase(0,1);
    }
    if (strNum == "0")
    {
        neg = false;
    }
    size = strNum.length();
    bigNum = new char [size];
    for (size_t i = 0; i < size; i++)
    {
        bigNum[i] = strNum[size - 1 - i];
    }
}

BigInt :: BigInt(const BigInt &Num) : size(Num.size), neg(Num.neg)
{
    bigNum = new char [size];
    for (size_t i = 0; i < size; i++)
    {
        bigNum[i] = Num.bigNum[i];
    }
}

BigInt :: BigInt(BigInt &&Num) : size(Num.size), neg(Num.neg)
// BigInt :: BigInt(BigInt &&Num) : size(std::move(Num.size)), neg(std::move(Num.neg))
{
    bigNum = Num.bigNum;
    Num.bigNum = nullptr;
    Num.size = 0;
    Num.neg = false;
}

BigInt & BigInt :: operator = (const BigInt &Num)
{
    if (this == &Num)
    {
        return *this;
    }
    delete [] bigNum;
    size = Num.size;
    neg = Num.neg;
    bigNum = new char [size];
    for (size_t i = 0; i < size; i++)
    {
        bigNum[i] = Num.bigNum[i];
    }
    return *this;
}

BigInt & BigInt :: operator = (BigInt &&Num)
{
    if (this == &Num)
    {
        return *this;
    }
    delete [] bigNum;
    bigNum = Num.bigNum;
    size = std::move(Num.size);
    neg = std::move(Num.neg); // from l-value to r-value
    Num.bigNum = nullptr;
    Num.size = 0;
    Num.neg = false;
    return *this;
}

BigInt :: ~BigInt()
{
    delete [] bigNum;
}

BigInt BigInt :: operator - () const
{
    BigInt Temp = *this;
    if (!((size == 1) && (bigNum[0] == '0')))
    {
        Temp.neg = !neg;
    }
    return Temp;
}

BigInt BigInt :: operator + (const BigInt &Num) const
{
    if (neg)
    {
        if (Num.neg)
        {
            return (-((-*this) + (-Num)));
        }
        else
        {
            return (-((-*this) - Num));
        }
    }
    else if (Num.neg)
    {
        return (*this - (-Num));
    }
    else 
    {
        if (size < Num.size)
        {
            return (Num + *this);
        }
        else
        {
            std::string res;
            char add = 0;
            for (size_t i = 0; i < Num.size; i++)
            {
                int sym;
                sym = (bigNum[i] - '0') + (Num.bigNum[i] - '0') + add;
                if (sym >= 10)
                {
                    add = 1;
                    sym %= 10;
                }
                else
                {
                    add = 0;
                }
                char res_sym = '0' + sym;
                res.insert(res.begin(), res_sym);
            }
            for (size_t i = Num.size; i < size; i++)
            {
                int sym;
                sym = (bigNum[i] - '0') + add;
                if (sym >= 10)
                {
                    add = 1;
                    sym %= 10;
                }
                else
                {
                    add = 0;
                }
                char res_sym = '0' + sym;
                res.insert(res.begin(), res_sym);
            }
            if (add)
            {
                res.insert(res.begin(), '1');
            }
            BigInt Res(res);
            return Res;
        }
    }
}

BigInt BigInt :: operator - (const BigInt &Num) const
{
    if (neg)
    {
        if (Num.neg)
        {
            return (-((-*this) - (-Num)));
        }
        else
        {
            return (-((-*this) + Num));
        }
    }
    else if (Num.neg)
    {
        return (*this + (-Num));
    }
    else 
    {
        if (*this < Num)
        {
            return (-(Num - *this));
        }
        else
        {
            std::string res;
            char add = 0;
            for (size_t i = 0; i < Num.size; i++)
            {
                int sym;
                sym = (bigNum[i] - '0') - add - (Num.bigNum[i] - '0');
                if (sym < 0)
                {
                    add = 1;
                    sym += 10;
                }
                else
                {
                    add = 0;
                }
                char res_sym = '0' + sym;
                res.insert(res.begin(), res_sym);
            }
            for (size_t i = Num.size; i < size; i++)
            {
                int sym;
                sym = (bigNum[i] - '0') - add;
                if (sym < 0)
                {
                    add = 1;
                    sym += 10;
                }
                else
                {
                    add = 0;
                }
                char res_sym = '0' + sym;
                res.insert(res.begin(), res_sym);
            }
            BigInt Res(res);
            return Res;
        }
    }
}

void BigInt :: pow_10_n (const size_t n)
{
    size += n;
    char *newBigNum = new char [size];
    for (size_t i = 0; i < n; i++)
    {
        newBigNum[i] = '0';
    }
    for (size_t i = n; i < size; i++)
    {
        newBigNum[i] = bigNum[i-n];
    }
    delete [] bigNum;
    bigNum = newBigNum;
}

BigInt BigInt :: operator * (const BigInt &Num) const
{
    if (neg)
    {
        if (Num.neg)
        {
            return ((-*this) * (-Num));
        }
        else
        {
            return (-((-*this) * Num));
        }
    }
    else if (Num.neg)
    {
        return (-(*this * (-Num)));
    }
    if ((size == 1) && (Num.size == 1))
    {
        BigInt Res((bigNum[0] - '0') * (Num.bigNum[0] - '0'));
        return Res;
    }
    std::string num1;
    std::string num2;
    for (size_t i = 0; i < size; i++)
    {
        num1.insert(num1.begin(), bigNum[i]);
    }
    for (size_t i = 0; i < Num.size; i++)
    {
        num2.insert(num2.begin(), Num.bigNum[i]);
    }
    int64_t diff = (size - Num.size);
    size_t len;
    if (diff < 0)
    {
        num1.insert(0, Num.size % 2 - diff, '0');
        num2.insert(0, (Num.size % 2), '0');
        len = Num.size + Num.size % 2;
    }
    else
    {
        num2.insert(num2.begin(), (size % 2 + diff), '0');
        num1.insert(num1.begin(), (size % 2), '0');
        len = size + size % 2;
    }
    BigInt Num11(num1.substr(len/2));
    BigInt Num12(num1.substr(0, len/2));
    BigInt Num21(num2.substr(len/2));
    BigInt Num22(num2.substr(0, len/2));

    BigInt Res1 = (Num11 * Num21);
    BigInt Res2 = (Num12 * Num22);
    BigInt Res3 = (((Num11 + Num12) * (Num21 + Num22)) - Res1 - Res2);
    Res3.pow_10_n(len/2);
    Res2.pow_10_n(len);
    
    return (Res1 + Res3 + Res2);
}

bool BigInt :: operator == (const BigInt &Num) const
{
    if ((size != Num.size) || (neg != Num.neg))
    {
        return 0;
    }
    bool flag = 1;
    for (size_t i = 0; i < size; i++)
    {
        flag = flag && (bigNum[i] == Num.bigNum[i]);
    }
    return flag;
}

bool BigInt :: operator != (const BigInt &Num) const
{
    return !(*this == Num);
}

bool BigInt :: operator < (const BigInt &Num) const
{
    if (*this == Num)
    {
        return 0;
    }
    if (neg)
    {
        if (Num.neg)
        {
            return ((- Num) < (- *this));
        }
        else
        {
            return 1;
        }
    }
    else if (Num.neg)
    {
        return 0;
    }
    else
    {
        if (size != Num.size)
        {
            return (size < Num.size);
        }
        else
        {
            size_t i = size - 1;
            while (bigNum[i] == Num.bigNum[i])
            {
                i--;
            }
            return (bigNum[i] < Num.bigNum[i]);
        }
    }
    bool flag = 1;
    
    return flag;
}

bool BigInt :: operator > (const BigInt &Num) const
{
    return !((*this < Num) || (*this == Num));
}

bool BigInt :: operator <= (const BigInt &Num) const
{
    return !(*this > Num);
}

bool BigInt :: operator >= (const BigInt &Num) const
{
    return !(*this < Num);
}


std::ostream & operator << (std::ostream &ostream, const BigInt &Num)
{
    if (Num.neg)
    {
        ostream << '-';
    }
    for (size_t i = Num.size; i > 0; i--)
    {
        ostream << Num.bigNum[i-1];
    }
    return ostream;
}