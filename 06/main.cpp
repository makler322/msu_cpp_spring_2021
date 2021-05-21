#include "format.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <cassert>

using namespace std;

void CorrectTest()
{
    string text = format("{1} + {1} = {0}", 2, "one");
    assert(text == "one + one = 2");
}

void EmptyTest()
{
    string text = format("","");
    assert(text == "");
}

void OneArgumentTest()
{
    string text = format("{0}","7");
    assert(text == "7");

    string text1 = format("77{0}","7");
    assert(text1 == "777");
}

void Many_N_Test()
{
    string text = format("{0}{1}{2}{3}{4}", 1, 2, 3, 4, 5);
    assert(text == "12345");

    string text1 = format("{0}{0}{0}{0}{0}", 1);
    assert(text1 == "11111");

    string text2 = format("{0}{1}{0}{2}{0}{3}{0}{4}{0}{5}{0}{6}{7}{8}{9}{10}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    assert(text2 == "121314151617891011");

}

void WrongBracketsTest()
{
    
    try 
    {
        std::string text = format("{}", 4);
    }

    catch(Bad_index& err) 
    {
        assert(err.what() == "expected '}', find not '}' at 1 element.");
    }
    catch(...) 
    {
        assert(1 == 0);
    }

    try 
    {
        std::string text = format("{1st}", 4);
    }

    catch(Bad_bracket& err) 
    {
        assert(err.what() == "expected '}', find not '}' at 2 element.");
    }
    catch(...) 
    {
        assert(1 == 0);
    }

    try 
    {
        std::string text = format("{0}{1}", 4);
    }

    catch(Bad_index& err) 
    {
        assert(err.what() == "wrong index at 5 element.");
    }
    catch(...) 
    {
        assert(1 == 0);
    }

}

void DifferentParametersTest() 
{
    try 
    {
        std::string text = format("{2} + {1} + {0} = 8 ", 4, "four");
    }
    catch(Bad_index& err) 
    {
        assert(err.what() == "wrong index at 2 element.");
    }
    catch(...) 
    {
        assert(1 == 0);
    }
    try 
    {
        std::string text = format("{0} + 12 = 8 ", 4, "four");
    }
    catch(Bad_index& err) 
    {
        assert(err.what() == "too much parameters at 13 element.");
    }
    catch(...) 
    {
        assert(1 == 0);
    }
}

void BracketsTest() 
{
    try 
    {
        std::string text = format("{0} + {1} + 0} = 8 ", 4, "four");
    }

    catch(Bad_bracket& err) 
    {
        assert(err.what() == "find '}', expected not '}' at 13 element.");
    }
    catch(...) 
    {
        assert(1 == 0);
    }
}

void IndexTest() 
{
    try 
    {
        std::string text = format("{0} + {1} + {-1} = 8 ", 4, "four", 6);
    }

    catch(Bad_bracket& err) 
    {
        assert(err.what() == "expected '}', find not '}' at 13 element.");
    }
    catch(...) 
    {
       assert(1 == 0);
    }
}

int main() 
{
    CorrectTest();
    EmptyTest();
    DifferentParametersTest();
    BracketsTest();
    IndexTest();
    OneArgumentTest();
    Many_N_Test();
    WrongBracketsTest();
    cout << "Success!\n";
    
    return 0;
}
