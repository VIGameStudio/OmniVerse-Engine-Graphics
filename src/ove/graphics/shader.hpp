#pragma once

#include <string>

#include <ove/core/types.hpp>
#include <ove/math/mat.hpp>
#include <ove/math/vec.hpp>

namespace gfxs {
using namespace core;
using namespace math;

struct shader_t {
  virtual void compile(const char *vsrc, const char *fsrc) = 0;

  virtual void bind() const = 0;

  virtual void unbind() const = 0;

  virtual void set_i32(const std::string &name, const i32 v) const = 0;

  virtual void set_f32(const std::string &name, const f32 v) const = 0;

  virtual void set_vec2f(const std::string &name, const vec2f &v) const = 0;

  virtual void set_vec3f(const std::string &name, const vec3f &v) const = 0;

  virtual void set_vec4f(const std::string &name, const vec4f &v) const = 0;

  virtual void set_mat3f(const std::string &name, const mat3f &v) const = 0;

  virtual void set_mat4f(const std::string &name, const mat4f &v) const = 0;
};
}
