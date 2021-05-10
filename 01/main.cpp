#include "Allocator.hpp"
#include <iostream>
#include <cassert>

void	testMakeAllocator(size_t test1)
{
	Allocator	all;
	char		*res;

	all.makeAllocator(test1);
	res = all.alloc(test1);
	for (size_t i = 0; i < test1 - 1; ++i)
		res[i] = 'a' + i % 26;
	res[test1 - 1] = '\0';
	res = all.alloc(1);
	assert(res == nullptr);
	all.makeAllocator(1);
	assert(all.alloc(2) == nullptr);
}

void	testAlloc()
{
	size_t		size = 100;
	Allocator	all;
	char		*res;

	all.makeAllocator(size);
	for (int i = 0; i < 10; ++i)
		assert(all.alloc(10) != nullptr);
	assert(all.alloc(1) == nullptr);
}

void	testReset()
{
	Allocator	all;

	all.makeAllocator(1);
	for (int i = 0; i < 10; ++i)
	{
		all.alloc(1);
		all.reset();
		assert(all.alloc(1) != nullptr);
	}
}

int main()
{
	testMakeAllocator(100);
	std::cout << "MakeAllocator() - success\n";
	testAlloc();
	std::cout << "Alloc() - success\n";
	testReset();
	std::cout << "Reset() - success\n";
}
