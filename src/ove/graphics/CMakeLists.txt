cmake_minimum_required(VERSION 2.8)

add_subdirectory(gl)
add_subdirectory(vk)

set(GRPH_LIB_HDRS
  "${CMAKE_CURRENT_SOURCE_DIR}/batch.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/renderer.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/model.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/procedural.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/scene.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/texture.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/light.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/material.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/mesh.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/shader.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/color.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/camera.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/viewport.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/vertex.hpp"
  "${GL_LIB_HDRS}"
  "${VK_LIB_HDRS}"
  PARENT_SCOPE
)

set(GRPH_LIB_SRCS
  "${GL_LIB_SRCS}"
  "${VK_LIB_SRCS}"
  "${CMAKE_CURRENT_SOURCE_DIR}/scene.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/procedural.cpp"
  PARENT_SCOPE
)
