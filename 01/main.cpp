#include "allocator.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void DefaultWorkTest()
{
    Allocator allocator;
    allocator.makeAllocator(10);
    assert(nullptr != allocator.alloc(5));
	assert(nullptr != allocator.alloc(5));
    allocator.reset();
    assert(nullptr != allocator.alloc(2));
	assert(nullptr != allocator.alloc(8));
}

void LimitAllocTest()
{
    Allocator allocator;
    allocator.makeAllocator(5);
    assert(nullptr != allocator.alloc(5));
	assert(nullptr == allocator.alloc(1));
    allocator.reset();
    assert(nullptr == allocator.alloc(6));
}

void AllocBeforeAllocatorTest()
{
    Allocator allocator;
    assert(nullptr == allocator.alloc(1));
    allocator.makeAllocator(5);
    assert(nullptr != allocator.alloc(5));
}

void TwoResetTest()
{
    Allocator allocator;
    allocator.makeAllocator(5);
    assert(nullptr != allocator.alloc(5));
    allocator.reset();
    allocator.reset();
    assert(nullptr != allocator.alloc(1));
    allocator.reset();
    allocator.reset();
    assert(nullptr == allocator.alloc(8));
}

void FiveAllocTest()
{
    Allocator allocator;
    allocator.makeAllocator(8);
    assert(nullptr != allocator.alloc(2));
    assert(nullptr != allocator.alloc(1));
    assert(nullptr != allocator.alloc(1));
    assert(nullptr != allocator.alloc(1));
    assert(nullptr == allocator.alloc(8));
}

void AllocAfterLimitTest()
{
    Allocator allocator;
    allocator.makeAllocator(8);
    assert(nullptr != allocator.alloc(2));
    assert(nullptr == allocator.alloc(7));
    assert(nullptr != allocator.alloc(1));
    assert(nullptr == allocator.alloc(6));
    assert(nullptr != allocator.alloc(5));
    assert(nullptr == allocator.alloc(1));
}

int main()
{   
    DefaultWorkTest();
    LimitAllocTest();
    AllocBeforeAllocatorTest();
    TwoResetTest();
    FiveAllocTest();
    AllocAfterLimitTest();

    cout << "Success \n";
    return 0;
}
