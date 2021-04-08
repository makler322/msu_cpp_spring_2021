#include "parser.hpp"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

string SimpleDigitTokenTest(uint64_t digit)
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

string SquareDigitTokenTest(uint64_t digit)
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

void FullEmptyTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SquareDigitTokenTest);
    parser.SetStringTokenCallback(LengthStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "";
    assert(parser.Parser(stringTest) == "Start " " End");
}

void SingleCharacterTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SimpleDigitTokenTest);
    parser.SetStringTokenCallback(SimpleStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "a 1 b 3";
    assert(parser.Parser(stringTest) == "Start " "String: a" "Digit: 1" "String: b" "Digit: 3" " End");
}

void OutOfUint64Test()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SimpleDigitTokenTest);
    parser.SetStringTokenCallback(SimpleStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "a 1 b 18446744073709551616 18446744073709551615";
    assert(parser.Parser(stringTest) == "Start " "String: a" "Digit: 1" "String: b" "String: 18446744073709551616" "Digit: 18446744073709551615" " End");
}

void OneSymbolTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SimpleDigitTokenTest);
    parser.SetStringTokenCallback(SimpleStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "a";
    assert(parser.Parser(stringTest) == "Start " "String: a" " End");
}

void OneDigitTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(SimpleDigitTokenTest);
    parser.SetStringTokenCallback(SimpleStringTokenTest);
    parser.SetStartCallback(SimpleStartTokenTest);
    parser.SetEndCallback(SimpleEndTokenTest);
    string stringTest = "1";
    assert(parser.Parser(stringTest) == "Start " "Digit: 1" " End");
}

int main()
{
    DefaultSimpleWorkTest();
    WithoutHandlersTest();
    SquareDigitAndLengthStringTest();
    EmptyTest();
    FullEmptyTest();
    SingleCharacterTest();
    OutOfUint64Test();
    OneSymbolTest();
    OneDigitTest();
    
    cout << "Success \n";
    return 0;
}
