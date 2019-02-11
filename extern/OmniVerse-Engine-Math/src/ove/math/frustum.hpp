#pragma once

#include <ove/core/util/types.hpp>

namespace math {
using namespace core;

template <typename T> struct frustum_t;
using frustumf = frustum_t<f32>;
using frustumd = frustum_t<f64>;

template <typename R> struct frustum_t {
  using real = R;
  real left, right;
  real top, bottom;
  real near, far;
};
}
