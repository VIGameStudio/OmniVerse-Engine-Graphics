#include "gl_shader.hpp"

namespace graphics {

void gl_shader_t::compile(const char* vsrc, const char* fsrc)
{
    GLint success = 0;
    GLchar errBuff[1024] = { 0 };

    // Create vertex shader
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vsrc, NULL);
    glCompileShader(vert);

    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(vert, sizeof(errBuff), NULL, errBuff);
        std::cerr << errBuff << std::endl;
        return; // false;
    }

    // Create fragment shader
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fsrc, NULL);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(frag, sizeof(errBuff), NULL, errBuff);
        std::cerr << errBuff << std::endl;
        return; // false;
    }

    // Create shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, vert);
    glAttachShader(m_id, frag);

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(frag, sizeof(errBuff), NULL, errBuff);
        std::cerr << errBuff << std::endl;
        return; // false;
    }

    glValidateProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(frag, sizeof(errBuff), NULL, errBuff);
        std::cerr << errBuff << std::endl;
        return; // false;
    }

    // No need for these so we can delete them
    glDeleteShader(vert);
    glDeleteShader(frag);
}

void gl_shader_t::bind() const { glUseProgram(m_id); }

void gl_shader_t::unbind() const { glUseProgram(0); }

void gl_shader_t::set_i32(const std::string& name, const i32 v) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), v);
}

void gl_shader_t::set_f32(const std::string& name, const f32 v) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), v);
}

void gl_shader_t::set_vec2f(const std::string& name, const vec2f& v) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, v.vptr());
}

void gl_shader_t::set_vec3f(const std::string& name, const vec3f& v) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, v.vptr());
}

void gl_shader_t::set_vec4f(const std::string& name, const vec4f& v) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, v.vptr());
}

void gl_shader_t::set_mat3f(const std::string& name, const mat3f& v) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, 1, v.vptr());
}

void gl_shader_t::set_mat4f(const std::string& name, const mat4f& v) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, 1, v.vptr());
}

}
