#pragma once

#include <ove/gfxs/config.hpp>
#include <ove/math/frustum.hpp>
#include <ove/math/mat.hpp>
#include <ove/math/quat.hpp>
#include <ove/math/vec.hpp>

namespace gfxs {
using namespace core;
using namespace math;

struct camera_t {
  vec3_t<real> position;
  quat_t<real> rotation;
  frustum_t<real> frustum;

  mat4_t<real> view;
  mat4_t<real> projection;
  mat4_t<real> combined;
};
}
