#include "gl_material.hpp"

#include <ove/core/hash.hpp>

namespace gfxs {

void gl_pbr_mat_t::draw(const camera_t &camera, const mat4f &model,
                        mesh_t *mesh) {

  m_shader->bind();

  m_shader->set_mat4f("Model", model);
  m_shader->set_mat4f("View", camera.view);
  m_shader->set_mat4f("Projection", camera.projection);

  // m_shader->set_vec3f("CamPos", camera.position);
  // m_shader->set_vec3f("LightPos", camLight ? camera.position : lightPos);
  // m_shader->set_vec3f("LightColor", lightColor);
  // m_shader->set_f32("LightIntensity", lightIntensity);

  m_shader->set_vec3f("Albedo", albedo);
  m_shader->set_f32("Metallic", metallic);
  m_shader->set_f32("Roughness", roughness);
  m_shader->set_f32("AO", ao);

  // albedoMap->bind(0);
  // m_shader->set_i32("AlbedoMap", 0);

  // normalMap->bind(1);
  // m_shader->set_i32("NormalMap", 1);

  // metallicMap->bind(2);
  // m_shader->set_i32("MetallicMap", 2);

  // roughnessMap->bind(3);
  // m_shader->set_i32("RoughnessMap", 3);

  // aoMap->bind(4);
  // pbrShader->set_i32("AOMap", 4);

  mesh->draw(m_meshMode);

  m_shader->unbind();
}

void gl_pbr_mat_t::parse(const json &mat) {
  auto type = mat["type"];
  auto shader = mat["shader"];
  auto textures = mat["textures"];
}

void gl_pbr_mat_t::dispose() {}

void gl_cubemap_mat_t::draw(const camera_t &camera, const mat4f &model,
                            mesh_t *mesh) {

  m_shader->bind();

  m_shader->set_mat4f("View", camera.view);
  m_shader->set_mat4f("Projection", camera.projection);
  m_shader->set_vec3f("Ambient", ambient);

  mesh->draw(m_meshMode);
  m_shader->unbind();
}

void gl_cubemap_mat_t::parse(const json &mat) {
  auto type = mat["type"];
  auto shader = mat["shader"];
  auto textures = mat["textures"];
}

void gl_cubemap_mat_t::dispose() {}
}
