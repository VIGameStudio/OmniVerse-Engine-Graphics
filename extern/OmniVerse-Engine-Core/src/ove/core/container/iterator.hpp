#pragma once

namespace core {

template <typename T>
struct iterator_t {
public:
    using value_type = T;
    using pointer_type = T*;
    using reference_type = T&;
    using iterator_type = iterator_t<T>;

    iterator_t(pointer_type ptr)
        : m_ptr(ptr)
    {
    }

public:
    inline reference_type operator*() { return *m_ptr; }

    inline pointer_type operator->() const { return m_ptr; }

    inline iterator_type operator++(int) { return iterator_type(m_ptr++); }

    inline iterator_type operator++() { return iterator_type(++m_ptr); }

    inline iterator_type operator--(int) { return iterator_type(m_ptr--); }

    inline iterator_type operator--() { return iterator_type(--m_ptr); }

    inline bool operator==(const iterator_type& a) { return m_ptr == a.m_ptr; }

    inline bool operator!=(const iterator_type& a) { return m_ptr != a.m_ptr; }

    inline bool operator<(const iterator_type& a) { return m_ptr < a.m_ptr; }

    inline bool operator>(const iterator_type& a) { return m_ptr > a.m_ptr; }

    inline bool operator<=(const iterator_type& a) { return m_ptr <= a.m_ptr; }

    inline bool operator>=(const iterator_type& a) { return m_ptr >= a.m_ptr; }

private:
    pointer_type m_ptr;
};

}
