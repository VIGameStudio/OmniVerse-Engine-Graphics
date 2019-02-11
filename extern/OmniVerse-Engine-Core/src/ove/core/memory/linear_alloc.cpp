#include "linear_alloc.hpp"

namespace core {

linear_alloc_t::linear_alloc_t(u64 size)
    : linear_alloc_t(size, malloc(size))
{
}

linear_alloc_t::linear_alloc_t(u64 size, void* start)
    : alloc_t(size, start)
    , m_pMarker(start)
{
    ASSERT(size > 0);
}

linear_alloc_t::~linear_alloc_t() { m_pMarker = nullptr; }

void* linear_alloc_t::allocate(u64 size, u8 align)
{
    ASSERT(size > 0);
    std::cout << "linear_alloc allocate.\n";

    u64 totalSize = size + align;
    if (m_memUsed + totalSize > m_size)
        return nullptr;

    ptrdiff adjustment = pmath::alignForward(reinterpret_cast<uptr>(m_pMarker), align);
    uptr rawAddress = reinterpret_cast<uptr>(m_pMarker);
    uptr alignedAddress = rawAddress + adjustment;
    u8* pAlignedMem = reinterpret_cast<u8*>(alignedAddress);
    pAlignedMem[-1] = adjustment;

    m_pMarker = (void*)(pAlignedMem + size);
    m_memUsed += size + adjustment;
    m_numAllocs++;

    return static_cast<void*>(pAlignedMem);
}

void linear_alloc_t::deallocate(void* p)
{
    std::cerr << "linear allocator does not support deallocate.\n";
}

void linear_alloc_t::clear()
{
    m_numAllocs = 0;
    m_memUsed = 0;

    m_pMarker = m_pStart;
}

}
