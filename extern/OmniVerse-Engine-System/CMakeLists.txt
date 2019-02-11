cmake_minimum_required(VERSION 3.2)

project(OVE_System)
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_REVISION_VERSION 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

option(OVE_SYSTEM_BUILD_DEMO "Build demo application." ON)
option(OVE_SYSTEM_BUILD_TEST "Build test targets." OFF)
option(OVE_SYSTEM_SHARED "Build as shared library." ON)

if(NOT ${OVE_SYSTEM_SHARED})
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(X11 REQUIRED)

    add_subdirectory(extern)
endif()

include_directories(src)

add_library(ove_system SHARED
    # System
    src/ove/system/fileio.hpp
    src/ove/system/fileio.cpp
    src/ove/system/input.hpp
    src/ove/system/window.hpp
    src/ove/system/window.cpp
    src/ove/system/x11/x11_window.hpp
    src/ove/system/x11/x11_window.cpp
    #src/ove/system/xcb/xcb_window.hpp
    #src/ove/system/xcb/xcb_window.cpp
    #src/ove/system/win/win_window.hpp
    #src/ove/system/win/win_window.cpp
    #src/ove/system/osx/osx_window.hpp
    #src/ove/system/osx/osx_window.cpp
)
target_link_libraries(ove_system ${X11_LIBRARY} ${OPENGL_LIBRARY} ${GLUT_LIBRARY})

if(${OVE_SYSTEM_BUILD_DEMO})
    add_executable(demo demo/main.cpp)
    target_link_libraries(demo ove_system)
endif(OVE_SYS_BUILD_DEMO)

if(${OVE_SYSTEM_BUILD_TEST})
    enable_testing()

    add_executable(_test test/_test.cpp)
    add_test(A_test _test)
    target_link_libraries(_test ove_system)
endif(OVE_SYS_BUILD_TEST)
