#pragma once

#include <ove/gfxs/material.hpp>

namespace gfxs {
struct gl_pbr_mat_t : public pbr_mat_t {

  virtual void draw(const camera_t &camera, const mat4f &model, mesh_t *mesh);

  virtual void dispose();

protected:
  virtual void parse(const json &mat);
};

struct gl_cubemap_mat_t : public cubemap_mat_t {

  virtual void draw(const camera_t &camera, const mat4f &model, mesh_t *mesh);

  virtual void dispose();

protected:
  virtual void parse(const json &mat);
};
}
