#pragma once

#include <type_traits>
#include <vector>

#include <ove/core/types.hpp>
#include <ove/gfxs/vertex.hpp>

namespace gfxs {
using namespace core;

enum mesh_mode { LINES, TRIANGLES };

struct mesh_t {
  virtual void submit(const vertex_array_t &data) = 0;

  virtual void draw(mesh_mode mode) const = 0;
};
}
