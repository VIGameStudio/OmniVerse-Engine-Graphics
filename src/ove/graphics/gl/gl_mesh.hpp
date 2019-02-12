#pragma once

#include <ove/graphics/gl/gl.hpp>
#include <ove/graphics/mesh.hpp>

namespace graphics {

struct gl_mesh_t : public mesh_t {
    virtual void submit(const vertex_array_t& data);

    virtual void draw(mesh_mode mode) const;

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    u32 m_vcount;
    u32 m_ecount;
};

}
