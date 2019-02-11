#pragma once

#include <ove/core/memory/alloc.hpp>

namespace core {

/*/// Stackalloc
class Stackalloc : public alloc
{
public:
Stackalloc(u64 size, void* start);
~Stackalloc();

void* allocate(u64 size, u8 alignment) override;

void deallocate(void* p) override;

private:
struct AllocationHeader
{
    #if ALLOC_DEBUG
    void* prev_address;
    #endif
    u8 adjustment;
};

#if ALLOC_DEBUG
void* prev_marker;
#endif

void*  marker;
};
*/

}
