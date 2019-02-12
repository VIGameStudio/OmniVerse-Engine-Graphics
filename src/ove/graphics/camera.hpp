#pragma once

#include <ove/math/frustum.hpp>
#include <ove/math/mat.hpp>
#include <ove/math/quat.hpp>
#include <ove/math/vec.hpp>

namespace graphics {

struct camera_t {
    math::vec3<real> position;
    math::quat_t<real> rotation;
    math::frustum_t<real> frustum;

    math::mat4_t<real> view;
    math::mat4_t<real> projection;
    math::mat4_t<real> combined;
};

}
