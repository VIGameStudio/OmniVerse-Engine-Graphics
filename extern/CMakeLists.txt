cmake_minimum_required(VERSION 3.2)

# OVE_Core submodule
set(OVE_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OmniVerse-Engine-Core)
if(EXISTS ${OVE_CORE_DIR})

    message("Updating core module ...")
    execute_process(COMMAND git pull origin master
        WORKING_DIRECTORY ${OVE_CORE_DIR})
    message("Core module updated.")

else()

    message("Initializing core module ...")
    execute_process(COMMAND git submodule add https://github.com/VIGameStudio/OmniVerse-Engine-Core.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND git submodule update --init --recursive OmniVerse-Engine-Core
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    message("Core module initialized.")

endif()

set(OVE_CORE_BUILD_DEMO OFF CACHE BOOL "enable X functionality" FORCE)
set(OVE_CORE_BUILD_TEST OFF CACHE BOOL "enable X functionality" FORCE)
add_subdirectory(OmniVerse-Engine-Core)
set(OVE_CORE_INCLUDE_DIR ${OVE_CORE_DIR}/src PARENT_SCOPE)



# OVE_Math submodule
set(OVE_MATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OmniVerse-Engine-Math)
if(EXISTS ${OVE_MATH_DIR})

    message("Updating math module ...")
    execute_process(COMMAND git pull origin master
        WORKING_DIRECTORY ${OVE_MATH_DIR})
    message("Math module updated.")

else()

    message("Initializing math module ...")
    execute_process(COMMAND git submodule add https://github.com/VIGameStudio/OmniVerse-Engine-Math.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND git submodule update --init --recursive OmniVerse-Engine-Math
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    message("Math module initialized.")

endif()

set(OVE_MATH_BUILD_DEMO OFF CACHE BOOL "enable X functionality" FORCE)
set(OVE_MATH_BUILD_TEST OFF CACHE BOOL "enable X functionality" FORCE)
set(OVE_MATH_SHARED ON CACHE BOOL "enable X functionality" FORCE)
add_subdirectory(OmniVerse-Engine-Math)
set(OVE_MATH_INCLUDE_DIR ${OVE_MATH_DIR}/src PARENT_SCOPE)



# OVE_System submodule
set(OVE_SYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OmniVerse-Engine-System)
if(EXISTS ${OVE_SYSTEM_DIR})

    message("Updating system module ...")
    execute_process(COMMAND git pull origin master
        WORKING_DIRECTORY ${OVE_SYSTEM_DIR})
    message("System module updated.")

else()

    message("Initializing system module ...")
    execute_process(COMMAND git submodule add https://github.com/VIGameStudio/OmniVerse-Engine-System.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND git submodule update --init --recursive OmniVerse-Engine-System
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    message("System module initialized.")

endif()

set(OVE_SYSTEM_BUILD_DEMO OFF CACHE BOOL "enable X functionality" FORCE)
set(OVE_SYSTEM_BUILD_TEST OFF CACHE BOOL "enable X functionality" FORCE)
set(OVE_SYSTEM_SHARED ON CACHE BOOL "enable X functionality" FORCE)
add_subdirectory(OmniVerse-Engine-System)
set(OVE_SYSTEM_INCLUDE_DIR ${OVE_SYSTEM_DIR}/src PARENT_SCOPE)



# GLAD generator
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GLAD)
if(NOT EXISTS ${GLAD_DIR})

    message("Initializing GLAD ...")
    set (GLAD_GEN_COMMAND "glad")
    set (GLAD_GEN_ARGS "--generator=c" "--profile=core" "--spec=gl" "--out-path=GLAD") #"--api=\"gl=3.2\""
    execute_process(COMMAND ${GLAD_GEN_COMMAND} ${GLAD_GEN_ARGS}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    message("GLAD initialized.")

endif()

add_library(GLAD SHARED ${GLAD_DIR}/src/glad.c)
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/include PARENT_SCOPE)
target_include_directories(GLAD PUBLIC ${GLAD_DIR}/include)
