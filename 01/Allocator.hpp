#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstdlib>

class Allocator
{
public:
	Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
private:
	char	*memory_ptr;
	size_t	offset;
	size_t	size_memory;
};

#endif
