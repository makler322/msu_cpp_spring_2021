#include "parser.hpp"
 
void TokenParser::SetStartCallback(const function<string ()>& start)
{
    StartToken = start;
}

void TokenParser::SetEndCallback(const function<string ()>& end)
{
    EndToken = end;
}

void TokenParser::SetDigitTokenCallback(const function<string (uint64_t)>& digit)
{
    DigitToken = digit;
}

void TokenParser::SetStringTokenCallback(const function<string (const string&)>& string)
{
    StringToken = string;
}

string TokenParser::ConvertToken(const string & token)
{
    bool flag = true;
    string answer = "";
    uint64_t i, my_number;
    for (i = 0; i < token.length(); i++)
    {
        if ((token[i] < '0') || (token[i] > '9'))
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {   
        try 
        {
            my_number = stoull(token);
        }
        catch (...)
        {
            my_number = 18446744073709551615U;
        }
        

        if (DigitToken != nullptr)
        {
            answer += DigitToken(my_number);
        }
        else
        {
            answer += to_string(my_number) + " ";
        }
        
    }
    else
    {
        if (StringToken != nullptr)
        {
            answer += StringToken(token);
        }
        else
        {
            answer += token + " ";
        }
    }
    return answer;
}

string TokenParser::Parser(const string & text)
{
    string answer = "", token = "";

    if (StartToken != nullptr)
    {
        answer += StartToken();
    }

    uint64_t i = 0;
    while (i < text.length())
    {
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n')
        {
            if (token != "")
            {
                answer += ConvertToken(token);
                token = "";
            }
        }
        else
        {
            token += text[i];
        }
        i++;
        if ((i == text.length()) && (token.length() > 0))
        {
            answer += ConvertToken(token);
            token = "";
        }
    }

    if (EndToken != nullptr)
    {
        answer += EndToken();
    }
    return answer;
}
