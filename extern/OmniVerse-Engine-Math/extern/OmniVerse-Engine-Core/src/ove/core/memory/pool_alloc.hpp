#pragma once

#include <ove/core/memory/alloc.hpp>

namespace core {

/// Poolalloc
/*class Poolalloc : public alloc
{
public:
Poolalloc(u64 objectSize, u8 objectAlignment, u64 size, void* mem);
~Poolalloc();

void* allocate(u64 size, u8 alignment) override;

void deallocate(void* p) override;

private:
u64     objectSize;
u8         objectAlignment;

void**     freeList;
};*/

}
