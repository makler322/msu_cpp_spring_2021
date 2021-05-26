#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>


using namespace std;

enum class Error
{
    InputFileError,
    OutputFileError,
    FilesError,
    ErrorMemory
};


const size_t memory = 8 * 1048576; // 8 * 1024 * 1024 байт доступно
const size_t mem_block = 1048576;
using my_type = uint64_t;
const size_t my_size = sizeof(uint64_t);
using my_it = istream_iterator<my_type>;
using my_pair = pair<my_it, my_it>;


void merge(const string & out_file_name, const vector<string> & file_names)
{
    ofstream file_out(out_file_name);
    if(!file_out)
    {
        throw Error::OutputFileError;
    }
    auto cmp = [](const my_pair & one, const my_pair & two)
    {
        return * one.first > * two.first;
    };
    priority_queue<my_pair, vector<my_pair>, decltype(cmp)> queue(cmp);
    fstream f_stream[file_names.size()];
    for (size_t i = file_names.size(); i > 0; i--)
    {
        f_stream[i-1].open(file_names[i - 1]);
        queue.emplace(my_it(f_stream[i - 1]), my_it());
    }
    while (!queue.empty())
    {
        auto cur_pair = queue.top();
        queue.pop();
        file_out << * cur_pair.first << ' ';
        cur_pair.first++;
        if (cur_pair.first != cur_pair.second)
        {
            queue.emplace(cur_pair);
        }
    }
    file_out.close();
}


void sort_file(const string & file_name, const string & out_file_name)
{
    size_t temp = 0;
    vector<string> file_names;
    ifstream file_in(file_name);
    if(!file_in)
    {
        throw Error::InputFileError;
    }
    auto * buf = new my_type[mem_block];
    temp += mem_block;
    int count = 1;
    string first_txt;
    string second_txt;
    while(!file_in.eof())
    {
        if (temp > memory)
        {
            throw Error::ErrorMemory;
        }
        file_in.read(reinterpret_cast<char*>(buf), mem_block);
        size_t right = file_in.gcount() / my_size;
        size_t mid = right / 2;
        if(right > 0)
        {
            first_txt = to_string(count++) + "f.txt";
            file_names.push_back(first_txt);
            second_txt = to_string(count++) + "f.txt";
            file_names.push_back(second_txt);
            thread first_thread([buf, mid]()
            {
                sort(buf, buf + mid);
            });
            thread second_thread([buf, mid, right]()
            {
                sort(buf + mid, buf + right);
            });
            first_thread.join();
            second_thread.join();
            ofstream out_first(first_txt);
            ofstream out_second(second_txt);
            if(!out_first || !out_second)
            {
                delete[] buf;
                throw Error::FilesError;
            }
            for (size_t i = 0; i < mid; i++)
            {
                out_first << buf[i] << " ";
            }
            for (size_t i = mid; i < right; i++)
            {
                out_second << buf[i] << " ";
            }
            out_first.close();
            out_second.close();
        }
    }
    file_in.close();
    temp = temp + sizeof(vector<string>) + (sizeof(string) * file_names.size());
    delete[] buf;
    temp -= mem_block;
    merge(out_file_name, file_names);
    for (auto & f: file_names)
    {
        remove(f.c_str());
    }
}