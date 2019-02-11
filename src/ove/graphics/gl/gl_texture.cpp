#include "gl_texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image_aug.h>

namespace gfxs {
void gl_texture_t::bind(u8 idx) const {
  glActiveTexture(GL_TEXTURE0 + idx);
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void gl_texture_t::unbind() const {
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_texture_t::submit(u32 width, u32 height, u32 bpp, bool mm, u8 *data) {
  if (m_id != -1) {
    if (width != m_width || height != m_height || bpp != m_bpp) {
      glDeleteTextures(1, &m_id);
      glGenTextures(1, &m_id);
    }
  } else {
    glGenTextures(1, &m_id);
  }

  glBindTexture(GL_TEXTURE_2D, m_id);

  setWrapMode();
  setFilter();

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    if (mm)
      glGenerateMipmap(GL_TEXTURE_2D);

    m_width = width;
    m_height = height;
    m_bpp = bpp;

  } else {
    // std::cout << "Failed to load texture" << std::endl;

    m_width = 0;
    m_height = 0;
    m_bpp = 0;
  }

  unbind();
}

void gl_texture_t::load(const std::string &filename) {
  i32 width, height, nrChannels;
  u8 *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
  submit(width, height, 32, true, data);
}

void gl_texture_t::dispose() {
  if (m_id != -1) {
    glDeleteTextures(1, &m_id);
    m_width = 0;
    m_height = 0;
    m_bpp = 0;
  }
}

void gl_texture_t::setWrapMode() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void gl_texture_t::setFilter() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void gl_cubemap_t::bind(u8 idx) const {
  glActiveTexture(GL_TEXTURE0 + idx);
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void gl_cubemap_t::unbind() const {
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void gl_cubemap_t::submit(u32 width, u32 height, u32 bpp, bool mm, u8 *data) {
  if (m_id != -1) {
    if (width != m_width || height != m_height || bpp != m_bpp) {
      glDeleteTextures(1, &m_id);
      glGenTextures(1, &m_id);
    }
  } else {
    glGenTextures(1, &m_id);
  }

  glBindTexture(GL_TEXTURE_2D, m_id);

  setWrapMode();
  setFilter();

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    if (mm)
      glGenerateMipmap(GL_TEXTURE_2D);

    m_width = width;
    m_height = height;
    m_bpp = bpp;

  } else {
    // std::cout << "Failed to load texture" << std::endl;

    m_width = 0;
    m_height = 0;
    m_bpp = 0;
  }

  unbind();
}

void gl_cubemap_t::load(const std::string &filename) {
  i32 width, height, nrChannels;
  u8 *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
  submit(width, height, 32, true, data);
}

void gl_cubemap_t::dispose() {
  if (m_id != -1) {
    glDeleteTextures(1, &m_id);
    m_width = 0;
    m_height = 0;
    m_bpp = 0;
  }
}

void gl_cubemap_t::setWrapMode() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void gl_cubemap_t::setFilter() {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
}
