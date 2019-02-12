#pragma once

#include <vector>

#include <ove/core/util/types.hpp>

namespace graphics {

using vertex_data = std::vector<f32>;
using element_data = std::vector<u32>;

struct vertex_array_t {
    vertex_data vertices;
    element_data elements;
    std::vector<u8> attributes;
};

}
