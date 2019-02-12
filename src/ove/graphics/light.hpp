#pragma once

#include <ove/math/mat.hpp>
#include <ove/math/vec.hpp>

namespace graphics {

struct light_t {
  math::vec3f position;
  math::vec3f color;
  math::f32 intensity;
  bool active;
};

}
