#pragma once

#include "impl/vmath_impl.hpp"
#include <ove/core/util/types.hpp>

namespace math {
using namespace core;

template <typename T, u8 D>
struct vec_t;

template <typename R>
using vec1 = vec_t<R, 1u>;

using vec1u = vec1<u32>;
using vec1i = vec1<i32>;
using vec1f = vec1<f32>;
using vec1d = vec1<f64>;

template <typename R>
using vec2 = vec_t<R, 2u>;
using vec2u = vec2<u32>;
using vec2i = vec2<i32>;
using vec2f = vec2<f32>;
using vec2d = vec2<f64>;

template <typename R>
using vec3 = vec_t<R, 3u>;
using vec3u = vec3<u32>;
using vec3i = vec3<i32>;
using vec3f = vec3<f32>;
using vec3d = vec3<f64>;

template <typename R>
using vec4 = vec_t<R, 4u>;
using vec4u = vec4<u32>;
using vec4i = vec4<i32>;
using vec4f = vec4<f32>;
using vec4d = vec4<f64>;

template <typename R, u8 D>
struct vec_t {
public:
    using type = vec_t<R, D>;
    using real = R;
    static const u8 Dim = D;
    static constexpr type zero() { return type(); }

public:
    vec_t()
        : data { 0 }
    {
    }

    vec_t(real v)
        : data { v }
    {
    }

public:
    inline const real* const vptr() const { return &data[0]; }

    inline real& operator[](u8 i) { return data[i]; }

    inline void operator()(real v)
    {
        for (u8 i = 0; i < Dim; ++i)
            data[i] = v;
    }

    union {
        real data[Dim];
    };
};

template <typename R>
struct vec_t<R, 1u> {
public:
    using type = vec_t<R, 1u>;
    using real = R;
    static const u8 Dim = 1u;
    static constexpr type zero() { return type(); }

public:
    vec_t()
        : data { 0 }
    {
    }

    vec_t(real v)
        : data { v }
    {
    }

public:
    inline const real* const vptr() const { return &data[0]; }

    inline real& operator[](u8 i) { return data[i]; }

    inline void operator()(real x) { this->x = x; }

    union {
        real data[Dim];
        struct {
            real x;
        };
    };
};

template <typename R>
struct vec_t<R, 2u> {
    using type = vec_t<R, 2u>;
    using real = R;
    static const u8 Dim = 2u;
    static constexpr type zero() { return type(); }

    vec_t()
        : data { 0 }
    {
    }
    vec_t(real v)
        : data { v }
    {
    }
    vec_t(real x, real y)
        : data { x, y }
    {
    }

    inline const real* const vptr() const { return &data[0]; }

    inline real& operator[](u8 i) { return data[i]; }
    inline void operator()(real x, real y)
    {
        this->x = x;
        this->y = y;
    }

    union {
        real data[Dim];
        struct {
            real x;
            real y;
        };
    };
};

template <typename R>
struct vec_t<R, 3u> {
    using type = vec_t<R, 3u>;
    using real = R;
    static const u8 Dim = 3u;
    static constexpr type zero() { return type(); }

    vec_t()
        : data { 0 }
    {
    }
    vec_t(real v)
        : data { v }
    {
    }
    vec_t(real x, real y, real z)
        : data { x, y, z }
    {
    }

    inline const real* const vptr() const { return &data[0]; }

    inline real& operator[](u8 i) { return data[i]; }
    inline void operator()(real x, real y, real z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    union {
        real data[Dim];
        struct {
            real x;
            real y;
            real z;
        };
    };
};

template <typename R>
struct vec_t<R, 4u> {
    using type = vec_t<R, 4u>;
    using real = R;
    static const u8 Dim = 4u;
    static constexpr type zero() { return type(); }

    vec_t()
        : data { 0 }
    {
    }
    vec_t(real v)
        : data { v }
    {
    }
    vec_t(real x, real y, real z, real w)
        : data { x, y, z, w }
    {
    }

    inline const real* const vptr() const { return &data[0]; }

    inline real& operator[](u8 i) { return data[i]; }
    inline void operator()(real x, real y, real z, real w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    union {
        real data[Dim];
        struct {
            real x;
            real y;
            real z;
            real w;
        };
    };
};
}
