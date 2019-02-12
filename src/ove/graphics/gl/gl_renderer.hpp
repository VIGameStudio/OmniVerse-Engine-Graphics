#pragma once

#include <ove/graphics/gl/gl.hpp>
#include <ove/graphics/renderer.hpp>

namespace graphics {

struct gl_renderer_t : public renderer_t {
    virtual void render(const camera_t& camera, const model_t& model) const;
};

}
