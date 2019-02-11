#include "gl_mesh.hpp"

namespace gfxs {
void gl_mesh_t::submit(const vertex_array_t &data) {
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  m_vcount = data.vertices.size();
  const size_t vsize = m_vcount * sizeof(f32);
  const f32 *vdata = &data.vertices[0];

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, vsize, vdata, GL_STATIC_DRAW);

  // Update attribute pointers.
  size_t stride = 0;
  for (auto attrib : data.attributes) {
    stride += attrib;
  }

  size_t offset = 0;
  size_t idx = 0;
  for (auto attrib : data.attributes) {
    glVertexAttribPointer(idx, attrib, GL_FLOAT, GL_FALSE, stride * sizeof(f32),
                          (void *)(offset * sizeof(f32)));
    glEnableVertexAttribArray(idx++);
    offset += attrib;
  }

  m_ecount = data.elements.size();
  const size_t esize = m_ecount * sizeof(u32);
  const u32 *edata = &data.elements[0];

  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, esize, edata, GL_STATIC_DRAW);

  glBindVertexArray(0);

  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void gl_mesh_t::draw(mesh_mode mode) const {
  glBindVertexArray(m_vao);

  GLuint glmode = 0;
  switch (mode) {
  case LINES:
    glmode = GL_LINES;
    break;
  case TRIANGLES:
    glmode = GL_TRIANGLES;
    break;
  }

  if (m_ecount > 0)
    glDrawElements(glmode, m_ecount, GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(glmode, 0, m_vcount);

  glBindVertexArray(0);
}
}
