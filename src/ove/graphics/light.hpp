#pragma once

#include <ove/math/mat.hpp>
#include <ove/math/vec.hpp>

namespace gfxs {
using namespace core;
using namespace math;

struct light_t {
  vec3f position;
  vec3f color;
  f32 intensity;
  bool active;
};
}
