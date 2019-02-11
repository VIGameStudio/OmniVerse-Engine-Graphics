#include "scene.hpp"

namespace gfxs {
void draw(renderer_t *renderer, model_t &model);

void scene_t::render(renderer_t *renderer) {
  for (auto node = root.begin(); node != root.end(); node++) {
    if (node->is<model_t>() && !node->isNull()) {
      auto model = node->get<model_t>();
      draw(renderer, *model);
    }
  }
}

void draw(renderer_t *renderer, model_t &model) {
  // TODO
}
}
