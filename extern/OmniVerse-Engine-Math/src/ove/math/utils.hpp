#pragma once

#include <iostream>

#include <ove/core/util/types.hpp>
#include <ove/math/vmath.hpp>

namespace math {
using namespace core;

template <typename T, u8 S> struct vec_t;

template <typename T> inline constexpr T rad2deg(const T &a) {
  return a * static_cast<T>(57.2957795131);
}

template <typename T> inline constexpr T deg2rad(const T &a) {
  return a * static_cast<T>(0.01745329252);
}

template <typename T>
inline constexpr T clamp(const T &v, const T &min, const T &max) {
  return v < min ? min : v > max ? max : v;
}

template <typename T> inline T abs(const T &v) { return std::abs(v); }

template <typename T>
inline constexpr size_t map(const vec_t<T, 3u> &v, size_t size) {
  return (int)v.x + (int)v.y * size + (int)v.z * size * size;
}
}
