cmake_minimum_required(VERSION 3.3)


# Marks header file as being overridden on a certain list of platforms.
#
# This avoids globbing as overriding for a new platform has to me marked explicitly,
# CMakeFile is touched and project is reconfigured.
#
# Usage: add_override(${PROJECT_NAME} settings.h PLATFORMS android linux osx)
function(add_override target filename)
  cmake_parse_arguments(ARG "" "" "PLATFORMS" ${ARGN})
  if(NOT ARG_PLATFORMS)
    message(FATAL_ERROR "Missing parameter PLATFORMS")
  endif()

  # Generate an _override.h header that is either empty (platform doesn't define overrides)
  # or includes the corresponding platform override header.
  # This _override.h has to be included by the generic header.

  # Determine filename of override header.
  string(REPLACE ".h" "_override.h" override_file ${filename})

  # Check if we have an override defined for this platform.
  if(${PLATFORM} IN_LIST ARG_PLATFORMS)
    message(STATUS "Override active for ${filename} on ${PLATFORM}")
    file(GENERATE OUTPUT ${override_file} CONTENT "#include \"overrides/${PLATFORM}/${filename}\"")

    # Add platform specific header to target sources (for IDEs)
    target_sources(${target} PRIVATE overrides/${PLATFORM}/${filename})
  else()
    message(STATUS "Override disabled for ${filename}, using generic implementation")
    string(CONCAT COMMENT "// No platform override defined for ${PLATFORM}. To add overrides:\n"
                          "// Create 'overrides/${PLATFORM}/${filename}' and redefine symbols from '${filename}'.\n"
                          "// Then adapt '${CMAKE_CURRENT_LIST_FILE}' and add '${PLATFORM}' to the 'add_override' call.")
    file(GENERATE OUTPUT ${override_file} CONTENT ${COMMENT})
  endif()

  # Add generated file to target sources (for IDEs)
  target_sources(${target} PRIVATE ${override_file})
endfunction()


# Project starts here
# override with -DPLATFORM=android for testing
project(platform_override)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(PLATFORM linux CACHE STRING "The platform we build for")

set(SOURCES main.cpp settings.h)
add_executable(${PROJECT_NAME} ${SOURCES})
add_override(${PROJECT_NAME} settings.h PLATFORMS android)  # Mention the platforms that you want to override to avoid GLOB
