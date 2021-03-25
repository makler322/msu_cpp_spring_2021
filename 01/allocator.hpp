#pragma once
#include <iostream>

using namespace std;


class Allocator
{
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
private:
    char* newMemory = nullptr;
    size_t offset = 0;
    size_t maxOffset = 0;
};

