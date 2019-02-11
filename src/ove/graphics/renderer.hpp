#pragma once

#include <ove/gfxs/camera.hpp>
#include <ove/gfxs/model.hpp>

namespace gfxs {
struct renderer_t {
  virtual void render(const camera_t &camera, const model_t &model) const = 0;
};
}
