#include "parser.hpp"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

string SimpleDigitTokenTest(int digit)
{
    return "Digit: " + to_string(digit);
}

string SimpleStringTokenTest(const string& string)
{
    return "String: " + string;
}

string SimpleStartTokenTest()
{
    return "Start ";
}

string SimpleEndTokenTest()
{
    return " End";
}

string SquareDigitTokenTest(int digit)
{
    return to_string(digit*digit);
}

string LengthStringTokenTest(const string& string)
{
    return "String: " + string + " length: " + to_string(string.length());
}


void DefaultSimpleWorkTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SimpleDigitTokenTest);
    parser.SetStringTokenCallback(SimpleStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "Hello world 03022000";
    assert(parser.Parser(stringTest) == "Start " "String: Hello" "String: world" "Digit: 3022000" " End");
}

void WithoutHandlersTest()
{
    TokenParser parser;
    string stringTest = "Hello\t\n\t   world \n03022000              \t";
    assert(parser.Parser(stringTest) == "Hello world 3022000 ");
}

void SquareDigitAndLengthStringTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SquareDigitTokenTest);
    parser.SetStringTokenCallback(LengthStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "Hello\t\n\t 9  \n05    \t";
    assert(parser.Parser(stringTest) == "Start " "String: Hello length: 5" "81" "25" " End");
}

void EmptyTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SquareDigitTokenTest);
    parser.SetStringTokenCallback(LengthStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "\t\n\t  \n    \t";
    assert(parser.Parser(stringTest) == "Start " " End");
}

int main()
{
    DefaultSimpleWorkTest();
    WithoutHandlersTest();
    SquareDigitAndLengthStringTest();
    EmptyTest();

    cout << "Success \n";
    return 0;
}
