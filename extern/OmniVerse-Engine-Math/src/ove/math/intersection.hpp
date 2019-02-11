#pragma once

#include <ove/math/obb.hpp>
#include <ove/math/ray.hpp>

namespace math {
template <typename A, typename B> bool intersects(const A &a, const B &b);

template <typename R, u8 D>
bool intersects(const ray_t<R, D> &r, const obb_t<R, D> &b) {
  const vec_t<R, D> irdir = 1.0 / r.direction;

  R tmp1 = (b.min.data[0] - r.origin.data[0]) * irdir.data[0];
  R tmp2 = (b.max.data[0] - r.origin.data[0]) * irdir.data[0];
  R tmin = min(tmp1, tmp2);
  R tmax = max(tmp1, tmp2);

  for (u8 i = 1; i < D; ++i) {
    tmp1 = (b.min.data[i] - r.origin.data[i]) * irdir.data[i];
    tmp2 = (b.max.data[i] - r.origin.data[i]) * irdir.data[i];

    tmin = max(tmin, min(tmp1, tmp2));
    tmax = min(tmax, max(tmp1, tmp2));
  }

  return tmax >= tmin;
}

template <typename R, u8 D>
bool intersects(const mray_t<R, D> &r, const obb_t<R, D> &b) {
  R tmp1 = (b.min.data[0] - r.origin.data[0]) * r.inv_direction.data[0];
  R tmp2 = (b.max.data[0] - r.origin.data[0]) * r.inv_direction.data[0];
  R tmin = min(tmp1, tmp2);
  R tmax = max(tmp1, tmp2);

  for (u8 i = 1; i < D; ++i) {
    tmp1 = (b.min.data[i] - r.origin.data[i]) * r.inv_direction.data[i];
    tmp2 = (b.max.data[i] - r.origin.data[i]) * r.inv_direction.data[i];

    tmin = max(tmin, min(tmp1, tmp2));
    tmax = min(tmax, max(tmp1, tmp2));
  }

  return tmax >= tmin;
}
}
