#pragma once
#include <functional>
#include <iostream>

using namespace std;


class TokenParser
{
private:
    function<string (uint64_t)> DigitToken = nullptr;
    function<string (const string&)> StringToken = nullptr;
    function<string ()> StartToken = nullptr;
    function<string ()> EndToken = nullptr;

public:
    void SetStartCallback(const function<string ()>& start);
    void SetEndCallback(const function<string ()>& end);
    void SetDigitTokenCallback(const function<string (uint64_t)>& digit);
    void SetStringTokenCallback(const function<string (const string&)>& string);
    string Parser(const string & text);
    string ConvertToken(const string & text);
};

