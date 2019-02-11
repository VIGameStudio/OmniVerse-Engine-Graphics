#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace math {
using namespace core;

template <typename R, u8 D> struct obb_t {
  using real = R;
  static const u8 Dim = D;
  vec_t<real, Dim> min;
  vec_t<real, Dim> max;
  mat_t<real, Dim, Dim> space;
};
}
