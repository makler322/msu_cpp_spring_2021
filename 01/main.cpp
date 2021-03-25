#include "allocator.hpp"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{   
    Allocator allocator;
	allocator.makeAllocator(sizeof(char) * 10);
	assert(nullptr != allocator.alloc(10 * sizeof(char)));
	assert(nullptr == allocator.alloc(1 * sizeof(char)));
	allocator.reset();
	assert(nullptr != allocator.alloc(5 * sizeof(char)));
	assert(nullptr != allocator.alloc(5 * sizeof(char)));
	assert(nullptr == allocator.alloc(1 * sizeof(char)));
    allocator.reset();
    assert(nullptr != allocator.alloc(7 * sizeof(char)));
}

int main()
{   
    test();
    cout << "Success \n";
    return 0;
}
