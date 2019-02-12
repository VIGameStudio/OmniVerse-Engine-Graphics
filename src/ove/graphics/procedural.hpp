#pragma once

#include <ove/graphics/vertex.hpp>
#include <ove/math/vec.hpp>

namespace graphics {
namespace procedural {

    namespace wire {
        void genPlane(vertex_array_t& data, vec2f size);

        void genBox(vertex_array_t& data, vec3f min, vec3f max);

        void genShpere(vertex_array_t& data, f32 r, u32 segments);
    }

    namespace unlit {
        void genPlane(vertex_array_t& data, vec2f size);

        void genCube(vertex_array_t& data, vec3f min, vec3f max);
    }

    namespace lit {
        void genPlane(vertex_array_t& data, vec2f size);

        void genCube(vertex_array_t& data, vec3f min, vec3f max);
    }
}
}
