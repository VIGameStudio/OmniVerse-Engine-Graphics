#pragma once

#include <utility>
#include <vector>

#include <ove/core/tree.hpp>
#include <ove/gfxs/camera.hpp>
#include <ove/gfxs/light.hpp>
#include <ove/gfxs/material.hpp>
#include <ove/gfxs/mesh.hpp>
#include <ove/gfxs/renderer.hpp>
#include <ove/gfxs/shader.hpp>

namespace gfxs {
using namespace core;
using namespace math;

struct scene_t : public tree_t {
  using model_node_t = node_t<model_t>;

  void render(renderer_t *renderer);

  void addCamera(const camera_t &camera) { m_cameras.emplace_back(camera); }

  void addLight(const light_t &light) { m_lights.emplace_back(light); }

  model_node_t addModel(const model_t &model, inode_t &parent) {
    return add(m_models, model, parent);
  }

private:
  template <typename C, typename T>
  tree_t::node_t<T> add(C &collection, const T &obj, inode_t &parent) {
    collection.resize(collection.size() + 1);

    for (auto &it : collection) {
      it.first->set(&it.second);
    }

    auto ptr = &collection[collection.size() - 1].second;
    auto node = parent.add(ptr);
    collection.emplace_back(std::make_pair(&node, obj));

    return node;
  }

  std::vector<camera_t> m_cameras;
  std::vector<light_t> m_lights;
  std::vector<std::pair<inode_t *, model_t>> m_models;
};
}
