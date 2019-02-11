#pragma once

#include <glad/glad.h>

#include <ove/gfxs/texture.hpp>

namespace gfxs {
struct gl_texture_t : public texture_t {
  gl_texture_t() : m_id(-1) {}

  virtual void bind(u8 idx) const;

  virtual void unbind() const;

  virtual void submit(u32 width, u32 height, u32 bpp, bool mm, u8 *data);

  virtual void load(const std::string &filename);

  virtual void dispose();

protected:
  virtual void setWrapMode();

  virtual void setFilter();

private:
  GLuint m_id;
};

struct gl_cubemap_t : public cubemap_t {
  gl_cubemap_t() : m_id(-1) {}

  virtual void bind(u8 idx) const;

  virtual void unbind() const;

  virtual void submit(u32 width, u32 height, u32 bpp, bool mm, u8 *data);

  virtual void load(const std::string &filename);

  virtual void dispose();

protected:
  virtual void setWrapMode();

  virtual void setFilter();

private:
  GLuint m_id;
};
}
