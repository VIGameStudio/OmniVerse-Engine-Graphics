#include "linear_alloc.hpp"

namespace core {

/// Proxyalloc_t
/*Proxyalloc_t::Proxyalloc_t(alloc_t& alloc_t)
    : alloc_t(alloc_t.getSize(), alloc_t.getStart()), alloc_t(alloc_t)
{
}

Proxyalloc_t::~Proxyalloc_t()
{
}

void* Proxyalloc_t::allocate(u64 size, u8 alignment)
{
    ASSERT(size != 0);
    numAllocs++;

    u64 mem = alloc_t.getUsedMemory();

    void* p = alloc_t.allocate(size, alignment);

    usedMem += alloc_t.getUsedMemory() - mem;

    return p;
}

void Proxyalloc_t::deallocate(void* p)
{
    numAllocs--;

    u64 mem = alloc_t.getUsedMemory();

    alloc_t.deallocate(p);

    usedMem -= mem - alloc_t.getUsedMemory();
}*/

}
