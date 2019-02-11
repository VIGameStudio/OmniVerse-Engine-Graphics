#pragma once

#include <json.hpp>
using json = nlohmann::json;

#include <ove/core/resource.hpp>
#include <ove/gfxs/camera.hpp>
#include <ove/gfxs/mesh.hpp>
#include <ove/gfxs/shader.hpp>
#include <ove/iout/fileio.hpp>
#include <ove/math/vec.hpp>

namespace gfxs {
using namespace core;
using namespace math;
using namespace iout;

struct texture_t;

struct material_t : resource_t {

  virtual void draw(const camera_t &camera, const mat4f &model,
                    mesh_t *mesh) = 0;

  virtual void dispose() = 0;

  virtual void load(const std::string &filename) {
    std::string tmp;
    file::read(filename, tmp);
    parse(json(tmp));
  }

  inline void setShader(shader_t *shader) { m_shader = shader; }

  inline void setMeshMode(mesh_mode meshMode) { m_meshMode = meshMode; }

protected:
  virtual void parse(const json &mat) = 0;

  shader_t *m_shader;
  mesh_mode m_meshMode;
};

struct pbr_mat_t : public material_t {
  vec3f albedo;
  f32 metallic;
  f32 roughness;
  f32 ao;

  virtual void draw(const camera_t &camera, const mat4f &model,
                    mesh_t *mesh) = 0;

  virtual void dispose() = 0;

protected:
  virtual void parse(const json &mat) = 0;

  texture_t *m_textures;
};

struct cubemap_mat_t : public material_t {
  vec3f ambient;

  virtual void draw(const camera_t &camera, const mat4f &model,
                    mesh_t *mesh) = 0;

  virtual void dispose() = 0;

protected:
  virtual void parse(const json &mat) = 0;

  texture_t *m_textures;
};
}
