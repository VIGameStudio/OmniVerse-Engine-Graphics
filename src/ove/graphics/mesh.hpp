#pragma once

#include <type_traits>
#include <vector>

#include <ove/core/util/types.hpp>
#include <ove/graphics/vertex.hpp>

namespace graphics {

enum mesh_mode {
    LINES,
    TRIANGLES
};

struct mesh_t {
    virtual void submit(const vertex_array_t& data) = 0;

    virtual void draw(mesh_mode mode) const = 0;
};

}
