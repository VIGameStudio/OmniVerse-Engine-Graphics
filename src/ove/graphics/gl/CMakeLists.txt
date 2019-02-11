cmake_minimum_required(VERSION 2.8)

set(GL_LIB_HDRS
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_renderer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_shader.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_mesh.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_texture.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_material.hpp"
  PARENT_SCOPE
)

set(GL_LIB_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_renderer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_shader.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_mesh.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_texture.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/gl_material.cpp"
  PARENT_SCOPE
)
