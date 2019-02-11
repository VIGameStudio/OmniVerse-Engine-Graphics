#pragma once

#include <ove/gfxs/material.hpp>
#include <ove/gfxs/mesh.hpp>
#include <ove/gfxs/shader.hpp>
#include <ove/math/mat.hpp>

namespace gfxs {
using namespace core;
using namespace math;

struct model_t {
  std::string name;
  mat4f transform;

  mesh_t *mesh;
  material_t *material;

  bool active;
};
}
