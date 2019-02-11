#pragma once

/**
 * TODO:
 * Revise
 */

#include <atomic>

namespace core {

template <typename T>
struct obj_t {
public:
    using type = T;

    obj_t(const T& v)
        : v(v)
    {
    }

    T v;
};

template <typename T>
using obj = obj_t<T>;
template <typename T>
using a_obj = std::atomic<obj_t<T>>;

using i8 = char;
using a_i8 = std::atomic<i8>;

using u8 = unsigned char;
using a_u8 = std::atomic<u8>;

using i16 = short;
using a_i16 = std::atomic<i16>;

using u16 = unsigned short;
using a_u16 = std::atomic<u16>;

using i32 = int;
using a_i32 = std::atomic<i32>;

using u32 = unsigned int;
using a_u32 = std::atomic<u32>;

using i64 = long;
using a_i64 = std::atomic<i64>;

using u64 = unsigned long;
using a_u64 = std::atomic<u64>;

using i128 = long long;
using a_i128 = std::atomic<i128>;

using u128 = unsigned long long;
using a_u128 = std::atomic<u128>;

using f32 = float;
using a_f32 = std::atomic<f32>;

using f64 = double;
using a_f64 = std::atomic<f64>;

using iptr = intptr_t;
using a_iptr = std::atomic<iptr>;

using uptr = uintptr_t;
using a_uptr = std::atomic<uptr>;

using ptrdiff = std::ptrdiff_t;
using a_ptrdiff = std::atomic<ptrdiff>;

using size_t = std::size_t;
using a_size_t = std::atomic<size_t>;
}
