#include "threadsort.hpp"
#include <iostream>
#include <cassert>

#define f_size 100000

using namespace std;

void makeInput()
{
    ofstream file("input.txt");
    ofstream expected("expected.txt");
    if(!file)
    {   
        throw Error::InputFileError;
    }

    vector<uint64_t> test;
    test.reserve(f_size);

    for(size_t i = 0; i < f_size; i++)
    {   
        uint64_t number = rand() % f_size;
        file.write(reinterpret_cast<char*>(& number), sizeof(uint64_t));
        test.push_back(number);
    }   

    sort(test.begin(), test.end());
    for (const auto& n: test)
        expected << n << " ";
}


void outputTest()
{
    ifstream f("output.txt");
    ofstream actual("actual.txt"); // Файл в который сохраняю то, что есть в output.txt через пробел

    my_type * mas = new my_type [f_size];
    for (int i = 0; i < f_size; i++)
    {
        uint64_t number;
        f >> number;
        mas[i] = number;
        actual << number << " ";
    }
    assert(is_sorted(mas, mas + f_size) == 1);
}


int main()
{
    makeInput();
    sort_file("input.txt", "output.txt");
    outputTest();
    cout << "Success!\n";
    
    return 0;
}