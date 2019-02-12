#pragma once

#include <ove/graphics/gl/gl.hpp>
#include <ove/graphics/shader.hpp>

namespace graphics {

struct gl_shader_t : public shader_t {
    virtual void compile(const char* vsrc, const char* fsrc);

    virtual void bind() const;

    virtual void unbind() const;

    virtual void set_i32(const std::string& name, const i32 v) const;

    virtual void set_f32(const std::string& name, const f32 v) const;

    virtual void set_vec2f(const std::string& name, const vec2f& v) const;

    virtual void set_vec3f(const std::string& name, const vec3f& v) const;

    virtual void set_vec4f(const std::string& name, const vec4f& v) const;

    virtual void set_mat3f(const std::string& name, const mat3f& v) const;

    virtual void set_mat4f(const std::string& name, const mat4f& v) const;

private:
    GLuint m_id;
};

}
