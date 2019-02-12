#include "gl_renderer.hpp"

#include <ove/graphics/gl/gl_mesh.hpp>
#include <ove/graphics/gl/gl_shader.hpp>

namespace graphics {

void gl_renderer_t::render(const camera_t& camera, const model_t& model) const
{
    auto mesh = static_cast<gl_mesh_t*>(model.mesh);
    auto material = model.material;

    material->draw(camera, model.transform, mesh);
}

}
