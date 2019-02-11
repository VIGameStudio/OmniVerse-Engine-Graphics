#pragma once

#include <ove/core/container/iterator.hpp>
#include <ove/core/memory/linear_alloc.hpp>
#include <ove/core/memory/new.hpp>
#include <ove/core/util/types.hpp>

#include <cstring>

namespace core {

template <typename T, typename alloc_type = linear_alloc_t>
struct vector_t {
public:
    using value_type = T;
    using iterator_type = iterator_t<T>;
    using size_type = size_t;

    vector_t(size_type capacity = 1)
        : m_size(0)
        , m_capacity(capacity)
        , m_pAlloc(new alloc_type(capacity))
        , m_pData(static_cast<value_type*>(m_pAlloc->start()))
    {
        ASSERT(capacity >= 1); // Capacity must be larger than 0!
    }

    ~vector_t()
    {
        delete_range(begin(), end());
        if (m_pData != nullptr)
            delete_range(begin(), end());
    }

public:
    inline size_type size() const { return m_size; }

    inline iterator_type begin() const { return iterator_type(m_pData); }

    inline iterator_type end() const { return iterator_type(m_pData + m_size); }

    inline void push_back(const value_type& value)
    {
        // Resize
        if (m_capacity == m_size) {
            m_capacity = m_capacity * 3;

            alloc_type* newAlloc = new alloc_type(m_capacity * sizeof(value_type));

            std::memcpy(newAlloc->start(), m_pData, m_size * sizeof(value_type));
            m_pData = static_cast<value_type*>(newAlloc->start());

            delete m_pAlloc;
            m_pAlloc = newAlloc;
        }

        new_<value_type>(m_pData + m_size, value);
        m_size++;
    }

    inline value_type& operator[](size_type idx)
    {
        return m_pData[idx];
    }

    inline const value_type& operator[](size_type idx) const
    {
        return m_pData[idx];
    }

private:
    static void delete_range(iterator_type begin, iterator_type end)
    {
        while (begin != end) {
            begin->~T();
            begin++;
        }
    }

private:
    size_type m_size;
    size_type m_capacity;
    alloc_type* m_pAlloc;
    T* m_pData;
};

}
