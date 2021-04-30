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
    DifferentParametersTest();
    BracketsTest();
    IndexTest();

    cout << "Success!\n";
    
    return 0;
}
