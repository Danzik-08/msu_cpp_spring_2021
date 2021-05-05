#include "Allocator.hpp"
#include <iostream>

void	checkMakeAllocator(size_t test1)
{
	Allocator	all;
	char		*res;

	std::cout << "----------CHECK_MAKE_ALLOCATOR---------\n";
	all.makeAllocator(test1);
	res = all.alloc(test1);
	for (size_t i = 0; i < test1 - 1; ++i)
		res[i] = 'a' + i % 26;
	res[test1 - 1] = '\0';
	std::cout << res << '\n';
	res = all.alloc(1);
	if (res == nullptr)
		std::cout << "makeAllocator alloced " << test1 << " bytes - GOOD\n";
	else
		std::cout << ":(\n";
	all.makeAllocator(1);
	if (all.alloc(2) == nullptr)
		std::cout << "makeAllocator realloced memory - GOOD\n";
}

void	checkAlloc()
{
	size_t		size = 100;
	Allocator	all;
	char		*res;

	std::cout << "----------CHECK_ALLOC---------\n";
	all.makeAllocator(size);
	for (int i = 0; i < 10; ++i)
		if (all.alloc(10) == nullptr)
		{
			std::cout << "BAD\n";
			return ;
		}
	if (all.alloc(1) == nullptr)
		std::cout << "alloc returned nullptr and every time worked correctly - GOOD\n";
}

void	checkReset()
{
	Allocator	all;

	std::cout << "----------CHECK_RESET---------\n";
	all.makeAllocator(1);
	for (int i = 0; i < 10; ++i)
	{
		all.alloc(1);
		all.reset();
		if (all.alloc(1) == nullptr)
		{
			std::cout << "Reset doesn't work correctly\n";
			return ;
		}
	}
	std::cout <<"Reset work correctly\n";
}

int main()
{
	checkMakeAllocator(100);
	checkAlloc();
	checkReset();
}
