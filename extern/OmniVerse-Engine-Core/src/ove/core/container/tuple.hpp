#pragma once

#include <type_traits>

#include <ove/core/util/meta.hpp>
#include <ove/core/util/types.hpp>

namespace core {
using namespace meta;

// choose N-th element in list <T...>
template <size_t N, typename... T>
struct choose_t;

template <size_t N, typename H, typename... T>
struct choose_t<N, H, T...> : choose_t<N - 1, T...> {
};

template <typename H, typename... T>
struct choose_t<0, H, T...> : id<H> {
};

template <size_t N, typename... T>
using choose = type_of<choose_t<N, T...>>;

// given L>=0, generate sequence <0, ..., L-1>
template <size_t L, size_t I = 0, typename S = sizes<>>
struct Range;

template <size_t L, size_t I, size_t... N>
struct Range<L, I, sizes<N...>> : Range<L, I + 1, sizes<N..., I>> {
};

template <size_t L, size_t... N>
struct Range<L, L, sizes<N...>> : sizes<N...> {
};

template <size_t L>
using range = type_of<Range<L>>;

// single tuple element
template <size_t N, typename T>
struct tuple_elem_t {
    using type = T;
    T elem;

public:
    T& get() { return elem; }
    const T& get() const { return elem; }
};

// tuple implementation
template <typename N, typename... T>
struct tuple_impl;

template <size_t... N, typename... T>
class tuple_impl<sizes<N...>, T...> : tuple_elem_t<N, T>... {
    template <size_t M>
    using pick = choose<M, T...>;
    template <size_t M>
    using elem = tuple_elem_t<M, pick<M>>;

public:
    template <size_t M>
    pick<M>& get() { return elem<M>::get(); }

    template <size_t M>
    const pick<M>& get() const { return elem<M>::get(); }
};

template <typename... T>
struct tuple_t : tuple_impl<range<sizeof...(T)>, T...> {
    static const size_t Size = sizeof...(T);
};
}
