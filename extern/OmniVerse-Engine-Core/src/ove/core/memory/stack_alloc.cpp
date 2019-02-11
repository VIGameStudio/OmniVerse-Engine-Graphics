#include "linear_alloc.hpp"

namespace core {

/// Stackalloc_t
/*Stackalloc_t::Stackalloc_t(u64 size, void* start)
    : alloc_t(size, start), marker(start)
{
    ASSERT(size > 0);

    #if ALLOC_DEBUG
    prev_marker     = nullptr;
    #endif
}

Stackalloc_t::~Stackalloc_t()
{
    #if ALLOC_DEBUG
    prev_marker     = nullptr;
    #endif

    marker          = nullptr;
}

void* Stackalloc_t::allocate(u64 size, u8 alignment)
{
    ASSERT(size != 0);

    u8 adjustment = ptrmath::alignForwardAdjustmentWithHeader(marker, alignment,
sizeof(AllocationHeader));

    if(usedMem + adjustment + size > allocSize)
        return nullptr;

    void* aligned_address = ptrmath::add(marker, adjustment);

    //Add Allocation Header
    AllocationHeader* header =
(AllocationHeader*)(ptrmath::subtract(aligned_address,
sizeof(AllocationHeader)));

    header->adjustment   = adjustment;

    #if ALLOC_DEBUG
    header->prev_address = prev_marker;

    prev_marker          = aligned_address;
    #endif

    marker = ptrmath::add(aligned_address, size);

    usedMem += size + adjustment;
    numAllocs++;

    return aligned_address;
}

void Stackalloc_t::deallocate(void* p)
{
    ASSERT( p == prev_marker );

    //Access the AllocationHeader in the bytes before p
    AllocationHeader* header = (AllocationHeader*)(ptrmath::subtract(p,
sizeof(AllocationHeader)));

    usedMem -= (uptr)marker - (uptr)p + header->adjustment;

    marker = ptrmath::subtract(p, header->adjustment);

    #if ALLOC_DEBUG
    prev_marker = header->prev_address;
    #endif

    numAllocs--;
}*/

}
