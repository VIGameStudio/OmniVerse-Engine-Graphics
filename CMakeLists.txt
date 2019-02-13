cmake_minimum_required(VERSION 3.2)

project(OVE_Graphics)
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_REVISION_VERSION 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

option(OVE_GRAPHICS_BUILD_DEMO "Build demo application." ON)
option(OVE_GRAPHICS_BUILD_TEST "Build test targets." OFF)
option(OVE_GRAPHICS_SHARED "Build as shared library." OFF)

if(NOT ${OVE_GRAPHICS_SHARED})
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(X11 REQUIRED)

    add_subdirectory(extern)
endif()

include_directories(src)

add_library(ove_graphics SHARED
    src/ove/graphics/dummy.hpp
    src/ove/graphics/dummy.cpp

    # Graphics
    #src/ove/graphics/batch.hpp
    #src/ove/graphics/camera.hpp
    #src/ove/graphics/color.hpp
    #src/ove/graphics/light.hpp
    #src/ove/graphics/mesh.hpp
    #src/ove/graphics/material.hpp
    #src/ove/graphics/shader.hpp
    #src/ove/graphics/procedural.hpp
    #src/ove/graphics/procedural.cpp
    #src/ove/graphics/texture.hpp
    #src/ove/graphics/renderer.hpp
    #src/ove/graphics/viewport.hpp
    #src/ove/graphics/vertex.hpp

    # OpenGL
    src/ove/graphics/gl/gl.hpp
    #src/ove/graphics/gl/gl_material.hpp
    #src/ove/graphics/gl/gl_material.cpp
    #src/ove/graphics/gl/gl_mesh.hpp
    #src/ove/graphics/gl/gl_mesh.cpp
    #src/ove/graphics/gl/gl_renderer.hpp
    #src/ove/graphics/gl/gl_renderer.cpp
    #src/ove/graphics/gl/gl_shader.hpp
    #src/ove/graphics/gl/gl_shader.cpp
    #src/ove/graphics/gl/gl_texture.hpp
    #src/ove/graphics/gl/gl_texture.cpp
)

target_include_directories(ove_graphics PUBLIC src ${OVE_CORE_INCLUDE_DIR} ${OVE_MATH_INCLUDE_DIR} ${OVE_SYSTEM_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
target_link_libraries(ove_graphics ove_core ove_math ove_system GLAD)

if(${OVE_GRAPHICS_BUILD_DEMO})
    add_executable(demo demo/main.cpp)
    target_link_libraries(demo ove_graphics ove_core ove_math ove_system)
endif()

if(${OVE_GRAPHICS_BUILD_TEST})
    enable_testing()

    add_executable(_test test/_test.cpp)
    add_test(A_test _test)
    target_link_libraries(_test ove_graphics)
endif()
