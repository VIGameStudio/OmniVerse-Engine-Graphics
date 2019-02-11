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

add_library(ove_graphics INTERFACE)
target_include_directories(ove_graphics INTERFACE src ${OVE_CORE_INCLUDE_DIR} ${OVE_MATH_INCLUDE_DIR} ${OVE_SYSTEM_INCLUDE_DIR})

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
