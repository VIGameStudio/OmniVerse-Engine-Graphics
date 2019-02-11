#include "linear_alloc.hpp"

namespace core {

/// Poolalloc_t
/*Poolalloc_t::Poolalloc_t(u64 objectSize, u8 objectAlignment, u64 size, void*
mem)
    : alloc_t(size, mem), objectSize(objectSize),
objectAlignment(objectAlignment)
{
    ASSERT(objectSize >= sizeof(void*));

    //Calculate adjustment needed to keep object correctly aligned
    u8 adjustment = ptrmath::alignForwardAdjustment(mem, objectAlignment);

    freeList = (void**)ptrmath::add(mem, adjustment);

    u64 numObjects = (size-adjustment)/objectSize;

    void** p = freeList;

    //Initialize free blocks list
    for(u64 i = 0; i < numObjects-1; i++)
    {
        *p = ptrmath::add(p, objectSize );
        p = (void**) *p;
    }

    *p = nullptr;
}

Poolalloc_t::~Poolalloc_t()
{
    freeList = nullptr;
}

void* Poolalloc_t::allocate(u64 size, u8 alignment)
{
    ASSERT(size == objectSize && alignment == objectAlignment);

    if(freeList == nullptr)
        return nullptr;

    void* p = freeList;

    freeList = (void**)(*freeList);

    usedMem += size;
    numAllocs++;

    return p;
}

void Poolalloc_t::deallocate(void* p)
{
    *((void**)p) = freeList;

    freeList = (void**)p;

    usedMem -= objectSize;
    numAllocs--;
}*/

}
