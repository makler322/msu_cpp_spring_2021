#include "allocator.hpp"
 
void Allocator::makeAllocator(size_t maxSize)
{
    if (newMemory == nullptr)
    {
        newMemory = new char [maxSize];
    }
    else
    {
        delete[] newMemory;
        newMemory = new char [maxSize];
    }
    offset = 0;
    maxOffset = maxSize;
};

char* Allocator::alloc(size_t size)
{
    if (size + offset > maxOffset)
    {
        return nullptr;
    }
    else
    {
        offset += size;
        return newMemory + offset - size;
    } 
};

void Allocator::reset()
{
    offset = 0;
};

Allocator::~Allocator()
{
    delete[] newMemory;
    offset = 0;
}
