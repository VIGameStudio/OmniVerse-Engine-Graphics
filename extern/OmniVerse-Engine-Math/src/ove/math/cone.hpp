#pragma once

#include <ove/core/util/types.hpp>
#include <ove/math/vec.hpp>

namespace math {
using namespace core;

template <typename R, u8 D> struct cone_t {
  using real = R;
  static const u8 Dim = D;
  real radius;
  real height;
};
}
