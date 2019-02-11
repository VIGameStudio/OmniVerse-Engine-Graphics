#include "alloc.hpp"

namespace core {
/// alloc_t (Base)
alloc_t::alloc_t(u64 size)
    : alloc_t(size, malloc(size))
{
}

alloc_t::alloc_t(u64 size, void* start)
    : m_size(size)
    , m_pStart(start)
    , m_memUsed(0)
    , m_numAllocs(0)
{
    ASSERT(size > 0);
}

alloc_t::~alloc_t()
{
    ASSERT(m_numAllocs == 0 && m_memUsed == 0);
    dispose();
}

}
