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

void ThreeAllocatorsTest()
{
    Allocator allocator1;
    Allocator allocator2;
    Allocator allocator3;
    allocator1.makeAllocator(6);
    allocator2.makeAllocator(7);
    assert(nullptr == allocator3.alloc(1));
    allocator3.makeAllocator(8);
    assert(nullptr != allocator1.alloc(2));
    assert(nullptr == allocator2.alloc(8));
    assert(nullptr != allocator3.alloc(1));
}

void ResetBeforAllocatorTest()
{
    Allocator allocator;
    allocator.reset();
    allocator.makeAllocator(1);
    assert(nullptr != allocator.alloc(1));
    assert(nullptr == allocator.alloc(1));
}

void ResetAndAllocBeforAllocatorTest()
{
    Allocator allocator;
    allocator.reset();
    assert(nullptr == allocator.alloc(1));
    allocator.makeAllocator(1);
    assert(nullptr != allocator.alloc(1));
    assert(nullptr == allocator.alloc(1));
}

void ResetAndAllocBeforThreeAllocatorsTest()
{
    Allocator allocator1;
    Allocator allocator2;
    Allocator allocator3;

    allocator1.reset();
    assert(nullptr == allocator1.alloc(1));
    allocator1.makeAllocator(6);
    assert(nullptr != allocator1.alloc(1));

    allocator2.reset();
    allocator2.makeAllocator(7);
    assert(nullptr != allocator2.alloc(1));

    assert(nullptr == allocator3.alloc(1));
    allocator3.makeAllocator(8);
    assert(nullptr != allocator3.alloc(1));

    assert(nullptr != allocator1.alloc(2));
    assert(nullptr != allocator2.alloc(5));
    assert(nullptr != allocator3.alloc(1));
}

void ThriceAllocatorAndAllocTest()
{
    Allocator allocator;
    assert(nullptr == allocator.alloc(1));
    allocator.makeAllocator(8);
    assert(nullptr != allocator.alloc(6));
    allocator.makeAllocator(4);
    assert(nullptr != allocator.alloc(3));
    allocator.makeAllocator(12);
    assert(nullptr != allocator.alloc(12));
    assert(nullptr == allocator.alloc(1));
    allocator.reset();
    assert(nullptr != allocator.alloc(5));
    assert(nullptr == allocator.alloc(10));
}

void ThriceAllocatorTest()
{
    Allocator allocator;
    allocator.makeAllocator(2);
    allocator.makeAllocator(4);
    allocator.makeAllocator(6);
    assert(nullptr != allocator.alloc(6));
    assert(nullptr == allocator.alloc(1));
    allocator.reset();
}

int main()
{   
    DefaultWorkTest();
    LimitAllocTest();
    AllocBeforeAllocatorTest();
    TwoResetTest();
    FiveAllocTest();
    AllocAfterLimitTest();
    ThreeAllocatorsTest();
    ResetBeforAllocatorTest();
    ResetAndAllocBeforAllocatorTest();
    ResetAndAllocBeforThreeAllocatorsTest();
    ThriceAllocatorAndAllocTest();
    ThriceAllocatorTest();
    
    cout << "Success \n";
    return 0;
}
