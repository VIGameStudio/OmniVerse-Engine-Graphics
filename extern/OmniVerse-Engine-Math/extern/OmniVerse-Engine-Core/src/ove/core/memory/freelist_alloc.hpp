#pragma once

#include <ove/core/memory/alloc.hpp>

namespace core {

/*/// FreeListalloc
class FreeListalloc : public alloc
{
public:
FreeListalloc(u64 size, void* start);
~FreeListalloc();

void* allocate(u64 size, u8 alignment) override;

void deallocate(void* p) override;

private:
struct AllocationHeader
{
    u64 size;
    u8     adjustment;
};

struct FreeBlock
{
    u64     size;
    FreeBlock* next;
};

FreeBlock* free_blocks;
};*/

}
