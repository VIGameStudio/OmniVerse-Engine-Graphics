cmake_minimum_required(VERSION 3.2)

# Find core module.
#find_path(OVE_CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OmniVerse-Engine-Core/src PARENT_SCOPE)

#if((NOT OVE_CORE_INCLUDE_DIR) OR (NOT EXISTS ${OVE_CORE_INCLUDE_DIR}))
    # Couldn't find the files for the core module or they don't exist.
#    message("Unable to find core module.")

    # Clone core git submodule.
#    execute_process(COMMAND git submodule update --init -- OmniVerse-Engine-Core
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    # Set OVE_CORE_INCLUDE_DIR properly
#    set(OVE_CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OmniVerse-Engine-Core/src PARENT_SCOPE)

#    add_subdirectory(OmniVerse-Engine-Core)

#else()
    # Found core module.
#    message("Found core module.")
#endif()
