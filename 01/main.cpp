#include "allocator.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{   
    Allocator allocator;
    assert(nullptr == allocator.alloc(1));
	allocator.makeAllocator(10);
	assert(nullptr != allocator.alloc(10));
	assert(nullptr == allocator.alloc(1));
	allocator.reset();
	assert(nullptr != allocator.alloc(5));
	assert(nullptr != allocator.alloc(5));
	assert(nullptr == allocator.alloc(1));
    allocator.reset();
    assert(nullptr != allocator.alloc(7));
    assert(nullptr == allocator.alloc(7));
    allocator.reset();
    allocator.reset();
    allocator.reset();
    assert(nullptr == allocator.alloc(11));
    allocator.makeAllocator(1);
    assert(nullptr == allocator.alloc(-2));
    assert(nullptr != allocator.alloc(0));
}

int main()
{   
    test();
    cout << "Success \n";
    return 0;
}
