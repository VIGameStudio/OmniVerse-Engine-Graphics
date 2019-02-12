#pragma once

#include <ove/graphics/camera.hpp>

namespace graphics {

struct renderer_t {
    virtual void render(const camera_t& camera, const model_t& model) const = 0;
};

}
