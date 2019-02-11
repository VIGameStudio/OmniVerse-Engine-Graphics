#pragma once

#include <cstddef>
#include <iostream>
#include <new>
#include <stdlib.h>

#include <ove/core/memory/ptr_math.hpp>
#include <ove/core/util/assert.hpp>
#include <ove/core/util/guard.hpp>
#include <ove/core/util/types.hpp>

namespace core {

class alloc_t : public nocopy {
public:
    alloc_t(u64 size);

    alloc_t(u64 size, void* start);

    virtual ~alloc_t();

public:
    virtual void* allocate(u64 size, u8 align = 4) = 0;

    virtual void deallocate(void* p) = 0;

    void* start() const;

    u64 size() const;

    u64 memUsed() const;

    u64 numAllocs() const;

    void dispose();

protected:
    u64 m_size;
    void* m_pStart;

    u64 m_memUsed;
    u64 m_numAllocs;
};

inline void* alloc_t::start() const { return m_pStart; }

inline u64 alloc_t::size() const { return m_size; }

inline u64 alloc_t::memUsed() const { return m_memUsed; }

inline u64 alloc_t::numAllocs() const { return m_numAllocs; }

inline void alloc_t::dispose()
{
    std::free(m_pStart);
    m_pStart = nullptr;
    m_size = 0;
}

template <class T>
struct vm_alloc_t {
public:
    typedef T value_type;

    vm_alloc_t();
    vm_alloc_t(alloc_t* alloc_t);

    template <class U>
    vm_alloc_t(const vm_alloc_t<U>&) noexcept {}

    template <class U>
    bool operator==(const vm_alloc_t<U>&) const noexcept
    {
        return true;
    }

    template <class U>
    bool operator!=(const vm_alloc_t<U>&) const noexcept
    {
        return false;
    }

    T* allocate(const u64 n) const;

    void deallocate(T* const p, u64) const noexcept;

private:
    alloc_t* m_pAlloc;
};

template <class T>
vm_alloc_t<T>::vm_alloc_t()
    : m_pAlloc(nullptr)
{
}

template <class T>
vm_alloc_t<T>::vm_alloc_t(alloc_t* alloc)
    : m_pAlloc(alloc)
{
    ASSERT(m_pAlloc != nullptr);
}

template <class T>
T* vm_alloc_t<T>::allocate(const u64 n) const
{
    if (n == 0) {
        return nullptr;
    } else if (n > static_cast<u64>(-1) / sizeof(T)) {
        throw std::bad_array_new_length();
        return nullptr;
    }

    void* pv;

    if (m_pAlloc != nullptr) {
        pv = m_pAlloc->allocate(n, alignof(T));
    } else {
        pv = std::malloc(n * sizeof(T));
    }

    if (!pv) {
        throw std::bad_alloc();
    }

    return static_cast<T*>(pv);
}

template <class T>
void vm_alloc_t<T>::deallocate(T* const p, u64) const noexcept
{
    if (m_pAlloc != nullptr) {
        m_pAlloc->deallocate(p);
    } else {
        std::free(p);
    }
}

}
