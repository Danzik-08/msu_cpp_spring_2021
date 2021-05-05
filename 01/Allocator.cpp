#include "Allocator.hpp"

Allocator::Allocator()
{
	memory_ptr = nullptr;
	offset = 0;
	size_memory = 0;
}

Allocator::~Allocator()
{
	delete [] memory_ptr;
}

void	Allocator::makeAllocator(size_t maxSize)
{
	if (memory_ptr != nullptr)
		delete [] memory_ptr;
	memory_ptr = new char [maxSize];
	size_memory = maxSize;
	offset = 0;
}

char	*Allocator::alloc(size_t size)
{
	char	*res;

	if (size + offset > size_memory)
		return nullptr;
	res = memory_ptr + offset;
	offset += size;
	return res;
}

void	Allocator::reset()
{
	offset = 0;
}
