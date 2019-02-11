#pragma once

#include <ove/gfxs/renderer.hpp>

namespace gfxs {
struct gl_renderer_t : public renderer_t {
  virtual void render(const camera_t &camera, const model_t &model) const;
};
}
