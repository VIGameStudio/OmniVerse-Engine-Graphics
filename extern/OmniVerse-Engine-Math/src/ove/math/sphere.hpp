#pragma once

#include <ove/core/util/types.hpp>

namespace math {
using namespace core;

template <typename R, u8 D> struct sphere_t {
  using real = R;
  static const u8 Dim = D;
  real radius;
};
}
