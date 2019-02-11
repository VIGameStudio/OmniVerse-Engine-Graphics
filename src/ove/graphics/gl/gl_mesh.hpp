#pragma once

#include <glad/glad.h>

#include <ove/gfxs/mesh.hpp>

namespace gfxs {
struct gl_mesh_t : public mesh_t {
  virtual void submit(const vertex_array_t &data);

  virtual void draw(mesh_mode mode) const;

private:
  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_ebo;
  u32 m_vcount;
  u32 m_ecount;
};
}
