#pragma once

#include <ove/core/memory/alloc.hpp>

namespace core {

template <class T>
T* new_(alloc_t& alloc);

template <class T>
T* new_(alloc_t& alloc, const T& val);

template <class T>
T* new_(void* dest);

template <class T>
T* new_(void* dest, const T& val);

template <class T>
void delete_(alloc_t& alloc, T& object);

// template<class T> T* _newN(alloc& alloc, u64 length);

// template<class T> void _deleteN(alloc& alloc, T* array);

template <class T>
T* new_(alloc_t& alloc)
{
    return new (alloc.allocate(sizeof(T), __alignof(T))) T;
}

template <class T>
T* new_(alloc_t& alloc, const T& val)
{
    return new (alloc.allocate(sizeof(T), __alignof(T))) T(val);
}

template <class T>
T* new_(void* dest)
{
    return new (dest) T;
}

template <class T>
T* new_(void* dest, const T& val)
{
    return new (dest) T(val);
}

template <class T>
void delete_(alloc_t& alloc, T& object)
{
    object.~T();
    alloc.deallocate(&object);
}

/*
template <class T>
T* _newN(alloc& alloc, u64 length)
{
    ASSERT(length != 0);

    u8 headerSize = sizeof(u64) / sizeof(T);

    if (sizeof(u64) % sizeof(T) > 0)
        headerSize += 1;

    // Allocate extra space to store array length in the bytes before the array
    T* p = ((T*)alloc.allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;

    *(((u64*)p) - 1) = length;

    for (u64 i = 0; i < length; i++)
        new (&p[i]) T;

    return p;
}

template <class T>
void _deleteN(alloc& alloc, T* array)
{
    ASSERT(array != nullptr);

    u64 length = *(((u64*)array) - 1);

    for (u64 i = 0; i < length; i++)
        array[i].~T();

    //Calculate how much extra memory was allocated to store the length before the array
    u8 headerSize = sizeof(u64) / sizeof(T);

    if (sizeof(u64) % sizeof(T) > 0)
        headerSize += 1;

    alloc.deallocate(array - headerSize);
}
*/

}
