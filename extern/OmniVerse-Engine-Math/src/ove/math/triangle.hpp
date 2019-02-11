#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace math {
using namespace core;

template <typename R, u8 D> struct triangle_t {
  using real = R;
  static const u8 Dim = D;
  vec_t<real, Dim> p1;
  vec_t<real, Dim> p2;
  vec_t<real, Dim> p3;
};
}
